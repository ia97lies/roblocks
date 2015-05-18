/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials.builder;

/**
 *
 * @author cli
 */
public class CommandHistory {

    public CommandHistory(int _size) {
        size = _size;
        command = new Command[size];
        top = 0;
    }

    void execute(Command _command) {
        if (top < size) {
            command[top] = _command;
            top++;
        } else {
            for (int i = 0; i < size - 1; i++) {
                command[i] = command[i+1];
            }
            command[top-1] = _command;
        }
        _command.execute();
    }

    void undo() {
        if (top > 0) {
            command[top - 1].undo();
            top--;
        }
    }

    void redo() {
        if (top < size) {
            command[top].execute();
            top++;
        }
    }
    Command command[];
    int top;
    int size;
}
