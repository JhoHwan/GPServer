pushd %~dp0

protoc.exe -I=./ --cpp_out=./ ./Enum.proto
protoc.exe -I=./ --cpp_out=./ ./Struct.proto
protoc.exe -I=./ --cpp_out=./ ./Protocol.proto

GenPackets.exe --path=./Protocol.proto --output=DummyClientPacketHandler --process=C
GenPackets.exe --path=./Protocol.proto --output=ClientPacketHandler --process=C
GenPackets.exe --path=./Protocol.proto --output=ServerPacketHandler --process=S

IF ERRORLEVEL 1 PAUSE

XCOPY /Y Enum.pb.h "../../../GameServer/Protobuf"
XCOPY /Y Enum.pb.cc "../../../GameServer/Protobuf"
XCOPY /Y Struct.pb.h "../../../GameServer/Protobuf"
XCOPY /Y Struct.pb.cc "../../../GameServer/Protobuf"
XCOPY /Y Protocol.pb.h "../../../GameServer/Protobuf"
XCOPY /Y Protocol.pb.cc "../../../GameServer/Protobuf"
XCOPY /Y ServerPacketHandler.h "../../../GameServer"

XCOPY /Y Enum.pb.h "C:\UnrealProject\GP\Source\GP\Network"
XCOPY /Y Enum.pb.cc "C:\UnrealProject\GP\Source\GP\Network"
XCOPY /Y Struct.pb.h "C:\UnrealProject\GP\Source\GP\Network"
XCOPY /Y Struct.pb.cc "C:\UnrealProject\GP\Source\GP\Network"
XCOPY /Y Protocol.pb.h "C:\UnrealProject\GP\Source\GP\Network"
XCOPY /Y Protocol.pb.cc "C:\UnrealProject\GP\Source\GP\Network"
XCOPY /Y ClientPacketHandler.h "C:\UnrealProject\GP\Source\GP"

XCOPY /Y Enum.pb.h "..\..\..\..\DummyClient"
XCOPY /Y Enum.pb.cc "..\..\..\..\DummyClient"
XCOPY /Y Struct.pb.h "..\..\..\..\DummyClient"
XCOPY /Y Struct.pb.cc "..\..\..\..\DummyClient"
XCOPY /Y Protocol.pb.h "..\..\..\..\DummyClient"
XCOPY /Y Protocol.pb.cc "..\..\..\..\DummyClient"
XCOPY /Y DummyClientPacketHandler.h "..\..\..\..\DummyClient"

DEL /Q /F *.pb.h
DEL /Q /F *.pb.cc
DEL /Q /F *.h

PAUSE