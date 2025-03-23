#include "pch.h"
#include "ConnectorWrapper.h"

DummyClientWrapper::ManagedConnector::ManagedConnector()
{
    _native = new shared_ptr<Connector>(make_shared<Connector>());
}

DummyClientWrapper::ManagedConnector::~ManagedConnector()
{
    delete _native;
}
