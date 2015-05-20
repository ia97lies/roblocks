/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials;

import static org.testng.Assert.*;
import org.testng.annotations.AfterClass;
import org.testng.annotations.AfterMethod;
import org.testng.annotations.BeforeClass;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

/**
 *
 * @author cli
 */
public class PlugNGTest {
    
    public PlugNGTest() {
    }

    @BeforeMethod
    public void setUpMethod() throws Exception {
    }

    @Test
    void testEmptyPlug() {
        Plug plug = new Plug();
        assertEquals(plug.getType(), Plug.Type.DEAF);
    }
    
    @Test
    void testTypedPlug() {
        Plug plug = new Plug(Plug.Type.DEAF);
        assertEquals(plug.getType(), Plug.Type.DEAF);
    }
    
    @Test
    void testInputPlug() {
        Plug plug = new Plug(Plug.Type.INPUT);
        assertEquals(plug.getType(), Plug.Type.INPUT);
    }
    
    @Test
    void testOutputPlug() {
        Plug plug = new Plug(Plug.Type.OUTPUT);
        assertEquals(plug.getType(), Plug.Type.OUTPUT);
    }
        
    @Test
    void testInOutPlug() {
        Plug plug = new Plug(Plug.Type.INOUT);
        assertEquals(plug.getType(), Plug.Type.INOUT);
    }

    @Test
    void testConnectToPlug() {
        Plug plug1 = new Plug();
        Plug plug2 = new Plug();
        plug1.connectPlug(plug2);
        assertEquals(plug1.getConnectedPlug(), plug2);
    }
    
    @Test
    void testGetDefaultValue() {
        Plug plug = new Plug();
        assertEquals(plug.getValue(), 0.0f);
    }
    
    @Test
    void testSetValue() {
        Plug plug = new Plug();
        plug.setValue(0.12f);
        assertEquals(plug.getValue(), 0.12f);
    }
}