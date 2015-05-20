package ch.artificials;

import com.jme3.app.SimpleApplication;
import com.jme3.collision.CollisionResult;
import com.jme3.collision.CollisionResults;
import com.jme3.input.ChaseCamera;
import com.jme3.input.MouseInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.MouseButtonTrigger;
import com.jme3.light.SpotLight;
import com.jme3.material.Material;
import com.jme3.scene.Geometry;
import com.jme3.scene.shape.Box;
import com.jme3.math.ColorRGBA;
import com.jme3.math.FastMath;
import com.jme3.math.Ray;
import com.jme3.math.Vector2f;
import com.jme3.math.Vector3f;
import com.jme3.scene.Node;
import com.jme3.scene.Spatial;
import com.jme3.scene.shape.Sphere;
import com.jme3.system.AppSettings;

/**
 * Sample 1 - how to get started with the most simple JME 3 application. Display
 * a blue 3D cube and view from all sides by moving the mouse and pressing the
 * WASD keys.
 */
public class Synthetics extends SimpleApplication {
    
    public static void main(String[] args) {
        AppSettings settings = new AppSettings(true);
        settings.setTitle("Synthetics 2");
        settings.setSettingsDialogImage("Interface/SplashScreen.png");
        Synthetics app = new Synthetics();
        app.setSettings(settings);
        app.start(); // start the game
    }
    
    private SpotLight spot;
    private Node robot;
    private Geometry mark;
    private ChaseCamera chaseCam;
    
    @Override
    public void simpleInitApp() {
        inputManager.setCursorVisible(true);
       
        initKeys();
        
        robot = new Node("Robot");
       
        Box shape = new Box(1, 1, 1);
        Geometry hub = new Geometry("Hub", shape);
        Material mat = new Material(assetManager, "Common/MatDefs/Light/Lighting.j3md");
        mat.setBoolean("UseMaterialColors", true);
        mat.setColor("Diffuse", ColorRGBA.Blue);
        mat.setColor("Ambient", ColorRGBA.Gray);
        mat.setColor("Specular", ColorRGBA.White);
        mat.setFloat("Shininess", 4f);
        hub.setMaterial(mat);

        robot.attachChild(hub);

        
        shape = new Box(1, 1, 1);
        hub = new Geometry("Hub", shape);
        hub.setLocalTranslation(3, 4, 5);
        mat = new Material(assetManager, "Common/MatDefs/Light/Lighting.j3md");
        mat.setBoolean("UseMaterialColors", true);
        mat.setColor("Diffuse", ColorRGBA.Blue);
        mat.setColor("Ambient", ColorRGBA.Gray);
        mat.setColor("Specular", ColorRGBA.White);
        mat.setFloat("Shininess", 4f);
        hub.setMaterial(mat);

        setupCam(hub);

        robot.attachChild(hub);
        
        Sphere sphere = new Sphere(30, 30, 0.5f);
        mark = new Geometry("Mark", sphere);
        mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        mat.setColor("Color", ColorRGBA.Red);
        mark.setMaterial(mat);

        spot = new SpotLight();
        spot.setDirection(cam.getDirection().normalizeLocal());
        spot.setColor(ColorRGBA.White);
        spot.setPosition(cam.getLocation());
        spot.setSpotRange(50f);
        spot.setSpotInnerAngle(FastMath.DEG_TO_RAD * 45);
        spot.setSpotOuterAngle(FastMath.DEG_TO_RAD * 50);
        rootNode.addLight(spot);
        rootNode.attachChild(robot);
    }
    
    private final static String SELECT = "Select";
    
    private void initKeys() {
        inputManager.addMapping(SELECT,
                new MouseButtonTrigger(MouseInput.BUTTON_LEFT));
        inputManager.addListener(actionListener, SELECT);
    }

    private ActionListener actionListener = new ActionListener() {
        public void onAction(String name, boolean keyPressed, float tpf) {
            if (name.equals(SELECT) && !keyPressed) {
                CollisionResults results = new CollisionResults();
                Vector2f click2d = inputManager.getCursorPosition();
                Vector3f click3d = cam.getWorldCoordinates(new Vector2f(click2d.x, click2d.y), 0f).clone();
                Vector3f dir = cam.getWorldCoordinates(new Vector2f(click2d.x, click2d.y), 1f).subtractLocal(click3d).normalizeLocal();
                Ray ray = new Ray(click3d, dir);
                robot.collideWith(ray, results);
                if (results.size() > 0) {
                    CollisionResult closest = results.getClosestCollision();
                    Vector3f pos = new Vector3f(closest.getGeometry().getWorldBound().getCenter().add(closest.getContactNormal().mult(1)));
                    mark.setLocalTranslation(pos);
                    rootNode.attachChild(mark);
                    chaseCam.setSpatial(closest.getGeometry());
                } else {
                    rootNode.detachChild(mark);
                }
            }
        }
    };
 
    private void setupCam(Spatial target) {
        flyCam.setEnabled(false);
        chaseCam = new ChaseCamera(cam, target, inputManager);
        chaseCam.setDragToRotate(true);
        chaseCam.setSmoothMotion(true);
        chaseCam.setChasingSensitivity(5);
        chaseCam.setRotationSpeed(10);
        chaseCam.setMinVerticalRotation(-FastMath.PI / 2);
        chaseCam.setMinDistance(5);
    }

    @Override
    public void simpleUpdate(float tpf) {
        spot.setDirection(cam.getDirection().normalize());
        spot.setPosition(cam.getLocation());
    }
}
