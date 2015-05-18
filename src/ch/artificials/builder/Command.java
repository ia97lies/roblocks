/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials.builder;

/**
 *
 * @author cli
 */
public interface Command {
    void execute();
    void undo();
}
