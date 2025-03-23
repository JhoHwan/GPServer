import argparse
import json
import os
from jinja2 import Template

class PacketGenerator:
    def __init__(self, config_path):
        with open(config_path, 'r') as f:
            self.config = json.load(f)

    def load_template(self, lang, template_type):
        template_path = self.config["templates"][lang][template_type]
        with open(template_path, 'r') as f:
            return Template(f.read())

    def convert_types(self, data, lang):
        type_mappings = {
            "csharp": {
                "BYTE": "byte",
                "int8": "sbyte",
                "int16": "short",
                "int32": "int",
                "int64": "long",
                "uint8": "byte",
                "uint16": "ushort",
                "uint32": "uint",
                "uint64": "ulong",
                "wchar": "char",
                "wstring": "string",
            },
            # Add more language mappings here if needed
        }
        mapping = type_mappings.get(lang, {})
        for item in data:
            for field in item["fields"]:
                field["type"] = mapping.get(field["type"], field["type"])
        return data

    def generate_code(self, lang, packet_data, struct_data, output_dir, target):
        # Load templates
        packet_template = self.load_template(lang, "packet")
        struct_template = self.load_template(lang, "struct")
        handler_template = self.load_template(lang, "handler")

        # Convert types
        self.convert_types(packet_data, lang)
        self.convert_types(struct_data, lang)

        # Generate packets
        send_packet_data, recv_packet_data = self.filter_packets_by_target(packet_data, target)
        packet_code = packet_template.render(packets=packet_data)
        handler_code = handler_template.render(sends=send_packet_data, recvs=recv_packet_data, class_name=self.config["output"][lang]["handler"].split('.', 1)[0])

        # Generate structs
        struct_code = struct_template.render(structs=struct_data)

        # Ensure output directory exists
        os.makedirs(output_dir, exist_ok=True)

        # Save outputs
        with open(os.path.join(output_dir, self.config["output"][lang]["packet"]), 'w') as f:
            f.write(packet_code)
        with open(os.path.join(output_dir, self.config["output"][lang]["handler"]), 'w') as f:
            f.write(handler_code)
        with open(os.path.join(output_dir, self.config["output"][lang]["struct"]), 'w') as f:
            f.write(struct_code)

        print(f"{lang.upper()} code generated in {output_dir}")


    @staticmethod
    def filter_packets_by_target(packet_data, target):
        recv_packet_data = []
        send_packet_data = []
        for packet in packet_data:
            packet_type = packet["packet_type"]
            if packet_type[0] == target:
                send_packet_data.append(packet)
            elif packet_type[1] == target:
                recv_packet_data.append(packet)
        return send_packet_data, recv_packet_data

def main():
    # 명령행 인자 정의
    parser = argparse.ArgumentParser(description="Packet and Struct Code Generator")
    parser.add_argument("--config", default="config.json", help="Path to the configuration JSON file")
    parser.add_argument("--packet", default="./Define/Packet.json", help="Path to the packet definition JSON file")
    parser.add_argument("--struct", default="./Define/Struct.json", help="Path to the struct definition JSON file")
    parser.add_argument("--lang", default="cpp", choices=["csharp", "cpp"], help="Target language for code generation")
    parser.add_argument("--target", default="G")
    parser.add_argument("--output", default="../Server/GameServer", help="Output directory for generated code")
    args = parser.parse_args()

    # 패킷 데이터 읽기
    with open(args.packet, 'r') as f:
        packet_data = json.load(f).get("packets", [])

    # 구조체 데이터 읽기
    with open(args.struct, 'r') as f:
        struct_data = json.load(f).get("structs", [])

    # PacketGenerator 초기화 및 코드 생성
    generator = PacketGenerator(args.config)
    generator.generate_code(args.lang, packet_data, struct_data, args.output, args.target)


if __name__ == "__main__":
    main()
