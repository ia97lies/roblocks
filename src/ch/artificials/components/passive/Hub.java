/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials.components.passive;

import ch.artificials.ComponentFactory;
import com.jme3.asset.AssetManager;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Box;

/**
 *
 * @author cli
 */
public class Hub implements ComponentFactory {
    public Node create(AssetManager assetManager) {
        Node node = new Node("Hub");
               
        Box shape = new Box(1, 1, 1);
        Geometry hub = new Geometry("Hub", shape);
        Material mat = new Material(assetManager, "Common/MatDefs/Light/Lighting.j3md");
        mat.setBoolean("UseMaterialColors", true);
        mat.setColor("Diffuse", ColorRGBA.Blue);
        mat.setColor("Ambient", ColorRGBA.Gray);
        mat.setColor("Specular", ColorRGBA.White);
        mat.setFloat("Shininess", 4f);
        hub.setMaterial(mat);
        node.attachChild(hub);
        
        // XXX: make it physical dont wait :)
        
        return node;
    }
}
