// **********************************************************************
//
// Copyright (c) 2003-2015 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

package test.Ice.acm;
import test.Ice.acm.Test._TestIntfDisp;

public class TestI extends _TestIntfDisp
{
    public void sleep(int delay, Ice.Current current)
    {
        synchronized(this)
        {
            try
            {
                wait(delay * 1000);
            }
            catch(java.lang.InterruptedException ex)
            {
            }
        }
    }

    public void sleepAndHold(int delay, Ice.Current current)
    {
        synchronized(this)
        {
            try
            {
                current.adapter.hold();
                wait(delay * 1000);
            }
            catch(java.lang.InterruptedException ex)
            {
            }
        }
    }

    public void interruptSleep(Ice.Current current)
    {
        synchronized(this)
        {
            notifyAll();
        }
    }
};
