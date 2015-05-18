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
public class CommandHistoryManyCommandTest {
    MockCommand command1;
    MockCommand command2;
    MockCommand command3;
    CommandHistory history;
    
    @BeforeMethod
    public void setUpMethod() throws Exception {
        command1 = new MockCommand();
        command2 = new MockCommand();
        command3 = new MockCommand();
        history = new CommandHistory(3);
        history.execute(command1);
        history.execute(command2);
        history.execute(command3);
    }
    
    @Test
    public void testExecuteFirstCommand() {
        assertEquals(command1.executeCalled, 1);
    }
    
    @Test
    public void testExecuteSecondCommand() {
        assertEquals(command2.executeCalled, 1);
    }
    
    @Test
    public void testExecuteThirdCommand() {
        assertEquals(command3.executeCalled, 1);
    }
    
    @Test
    public void testOneUndo() {
        history.undo();
        assertEquals(command3.undoCalled, 1);
    }
    
    @Test
    public void testTwoUndo() {
        history.undo();
        history.undo();
        assertEquals(command2.undoCalled, 1);
    }
            
    @Test
    public void testThreeUndo() {
        history.undo();
        history.undo();
        history.undo();
        assertEquals(command1.undoCalled, 1);
    }

    @Test
    public void testExecuteOneMoreUndoThreeTimes() {
        MockCommand command = new MockCommand();
        history.execute(command);
        history.undo();
        history.undo();
        history.undo();
        assertEquals(command1.undoCalled, 0);
        assertEquals(command.undoCalled, 1);
    }

}