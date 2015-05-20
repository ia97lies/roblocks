/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials;

/**
 *
 * @author cli
 */
class Plug {

    Plug(Type _type) {
        type = _type;
    }
    
    Plug() {
        this(Type.DEAF);
    }

    Type getType() {
        return type;
    }
    
    void connectPlug(Plug _plug) {
        plug = _plug;
    }
    
    Plug getConnectedPlug() {
        return plug;
    }

    void setValue(float _value) {
        value = _value;
    }
    
    float getValue() {
        return value;
    }
    
    public enum Type { DEAF, INPUT, OUTPUT, INOUT };
    private Type type;
    private Plug plug;
    private float value;
}
