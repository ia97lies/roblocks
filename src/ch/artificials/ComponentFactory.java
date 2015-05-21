/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials;

import com.jme3.asset.AssetManager;
import com.jme3.scene.Node;

/**
 *
 * @author cli
 */
public interface ComponentFactory {
    public Node create(AssetManager assetManager);
}
