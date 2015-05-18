/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials.builder;

import static org.testng.Assert.*;
import org.testng.annotations.BeforeMethod;
import org.testng.annotations.Test;

/**
 *
 * @author cli
 */
public class CommandHistoryOneComandTest {

    MockCommand command;
    CommandHistory history;
    
    @BeforeMethod
    public void setUpMethod() throws Exception {
        command = new MockCommand();
        history = new CommandHistory(1);
        history.execute(command);
    }

    @Test
    public void testExecute() {
        assertEquals(command.executeCalled, 1);
    }
    
    @Test
    public void testUndo() {
        history.undo();
        assertEquals(command.undoCalled, 1);
    }
    
    @Test
    public void testOneMoreExecute() {
        MockCommand mockCommand = new MockCommand();
        history.execute(mockCommand);
        assertEquals(mockCommand.executeCalled, 1);
    }
}