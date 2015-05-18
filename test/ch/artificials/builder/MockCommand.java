/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials.builder;


/**
 * Command Mockup
 * @author cli
 */
public class MockCommand implements Command {
    public int executeCalled;
    public int undoCalled;
    public MockCommand() { 
        executeCalled = 0;
        undoCalled = 0;
    }
    public void execute() { executeCalled++; }
    public void undo() { undoCalled++; }
}
