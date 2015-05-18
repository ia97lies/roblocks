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
public class CommandHistoryTwoCommandTest {
    MockCommand command1;
    MockCommand command2;
    CommandHistory history;
    
    @BeforeMethod
    public void setUpMethod() throws Exception {
        command1 = new MockCommand();
        command2 = new MockCommand();
        history = new CommandHistory(2);
        history.execute(command1);
        history.execute(command2);
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
    public void testUndoOneCommand() {
        history.undo();
        assertEquals(command2.undoCalled, 1);
    }
    
    @Test
    public void testUndoBothCommands() {
        history.undo();
        history.undo();
        assertEquals(command1.undoCalled, 1);
    }

    @Test
    public void testUndoTooMany() {
        history.undo();
        history.undo();
        history.undo();
        assertEquals(command1.undoCalled, 1);
    }
    
    @Test
    public void testRedo() {
        history.undo();
        history.redo();
        assertEquals(command2.executeCalled, 2);
    }
    
    @Test
    public void testRedoOneUndo() {
        history.undo();
        history.undo();
        history.redo();
        assertEquals(command1.executeCalled, 2);
    }
    
    @Test
    public void testRedoTwoUndo() {
        history.undo();
        history.undo();
        history.redo();
        history.redo();
        assertEquals(command2.executeCalled, 2);
    }
    
    @Test 
    public void testRedoTooMany() {
        history.undo();
        history.redo();
        history.redo();
        assertEquals(command2.executeCalled, 2);
    }
    
    @Test
    public void testExecuteOneMore() {
        MockCommand mockCommand = new MockCommand();
        history.execute(mockCommand);
        assertEquals(mockCommand.executeCalled, 1);
    }
}