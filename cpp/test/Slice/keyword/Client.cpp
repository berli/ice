// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <Key.h>

using namespace std;

class breakI : public _cpp_and::_cpp_break
{
public:
    virtual void case_async(const ::_cpp_and::AMD_break_casePtr& cb, ::Ice::Int, const ::Ice::Current&)
    {
        cb->ice_response(0);
    }
};

class charI: public _cpp_and::_cpp_char
{
public:
    virtual void _cpp_explicit(const ::Ice::Current& current)
    {
        assert(current.operation == "explicit");
    }
};

class complI: public _cpp_and::_cpp_compl
{
public:
    virtual void foo(const _cpp_and::charPrx&, Ice::Int&, const ::Ice::Current&)
    {
    }
};

class doI : public _cpp_and::_cpp_do
{
public:
    virtual void case_async(const ::_cpp_and::AMD_break_casePtr&, ::Ice::Int, const ::Ice::Current&)
    {
    }
    virtual void _cpp_explicit(const ::Ice::Current&) 
    {
    }
    virtual void foo(const _cpp_and::charPrx&, Ice::Int&, const ::Ice::Current&)
    {
    }
};

class friendI : public _cpp_and::_cpp_friend
{
public:
    virtual _cpp_and::_cpp_auto
    _cpp_goto(_cpp_and::_cpp_continue, const _cpp_and::_cpp_auto&, const _cpp_and::deletePtr&,
              const _cpp_and::complPtr&, const _cpp_and::doPtr&, const _cpp_and::breakPrx&,
              const _cpp_and::charPrx&, const _cpp_and::complPrx&, const _cpp_and::doPrx&,
              ::Ice::Int, ::Ice::Int, ::Ice::Int, ::Ice::Int)
    {
        return _cpp_and::_cpp_auto();
    }
};

class fooI : public _cpp_and::AMI_compl_foo
{
public:

    virtual void ice_response(Ice::Int)  {}
    virtual void ice_exception(const ::Ice::Exception&) {}
};
   
//
// This section of the test is present to ensure that the C++ types
// are named correctly. It is not expected to run.
//
void
testtypes()
{
    _cpp_and::_cpp_continue a = _cpp_and::_cpp_asm;
    assert(a);

    _cpp_and::_cpp_auto b;
    b._cpp_default = 0;

    _cpp_and::deletePtr c = new _cpp_and::_cpp_delete();
    c->_cpp_else = "";

    _cpp_and::breakPrx d;
    int d2;
    d->_cpp_case(0, d2);
    _cpp_and::breakPtr d1 = new breakI();

    _cpp_and::charPrx e;
    e->_cpp_explicit();
    _cpp_and::charPtr e1 = new charI();

    _cpp_and::complPrx f;
    f->foo_async(new fooI(), e);
    _cpp_and::complPtr f1 = new complI();

    _cpp_and::doPrx g;
    g->_cpp_case(0, d2);
    g->_cpp_explicit();
    _cpp_and::doPtr g1 = new doI();

    _cpp_and::_cpp_extern h;
    _cpp_and::_cpp_for i;
    _cpp_and::_cpp_return j;
    j._cpp_signed = 0;
    _cpp_and::_cpp_sizeof k;
    k._cpp_static = 0;
    k._cpp_switch = 1;
    k._cpp_signed = 2;

    _cpp_and::friendPtr l = new friendI();

    const int m  = _cpp_and::_cpp_template;
    assert(m == _cpp_and::_cpp_template);
}

int
run(const Ice::CommunicatorPtr& communicator)
{
    communicator->getProperties()->setProperty("TestAdapter.Endpoints", "default -p 12010 -t 10000:udp");
    Ice::ObjectAdapterPtr adapter = communicator->createObjectAdapter("TestAdapter");
    adapter->add(new charI, communicator->stringToIdentity("test"));
    adapter->activate();

    cout << "Testing operation name... " << flush;
    _cpp_and::charPrx p = _cpp_and::charPrx::uncheckedCast(
        adapter->createProxy(communicator->stringToIdentity("test")));
    p->_cpp_explicit();
    cout << "ok!" << endl;

    return EXIT_SUCCESS;
}

int
main(int argc, char* argv[])
{
    int status;
    Ice::CommunicatorPtr communicator;

    try
    {
        Ice::InitializationData initData;
        initData.properties = Ice::createProperties(argc, argv);
        communicator = Ice::initialize(argc, argv, initData);
        status = run(communicator);
    }
    catch(const Ice::Exception& ex)
    {
        cerr << ex << endl;
        status = EXIT_FAILURE;
    }

    if(communicator)
    {
        try
        {
            communicator->destroy();
        }
        catch(const Ice::Exception& ex)
        {
            cerr << ex << endl;
            status = EXIT_FAILURE;
        }
    }

    return status;
}