// **********************************************************************
//
// Copyright (c) 2003-2007 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#include <Ice/Ice.h>
#include <TestCommon.h>
#include <Test.h>

using namespace std;

void
oneways(const Ice::CommunicatorPtr& communicator, const Test::MyClassPrx& proxy)
{
    Test::MyClassPrx p = Test::MyClassPrx::uncheckedCast(proxy->ice_oneway());
    
    {
        p->opVoid();
    }

    {
        Ice::Byte b;
        Ice::Byte r;

        try
        {
            r = p->opByte(Ice::Byte(0xff), Ice::Byte(0x0f), b);
            test(false);
        }
        catch(const Ice::TwowayOnlyException&)
        {
        }
    }

}