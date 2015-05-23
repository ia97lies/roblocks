/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package ch.artificials;

import com.jme3.asset.AssetManager;
import com.jme3.bullet.BulletAppState;
import com.jme3.math.Vector3f;
import com.jme3.scene.Node;

/**
 *
 * @author cli
 */
public interface ComponentFactory {
    public Node create(Vector3f loc, AssetManager assetManager, BulletAppState bulletAppState);
}
