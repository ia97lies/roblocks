package ch.artificials;

import ch.artificials.components.passive.HubFactory;
import com.bulletphysics.dynamics.constraintsolver.HingeConstraint;
import com.jme3.app.SimpleApplication;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.collision.shapes.CompoundCollisionShape;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.bullet.joints.HingeJoint;
import com.jme3.bullet.joints.Point2PointJoint;
import com.jme3.bullet.joints.SixDofJoint;
import com.jme3.collision.CollisionResult;
import com.jme3.collision.CollisionResults;
import com.jme3.input.ChaseCamera;
import com.jme3.input.KeyInput;
import com.jme3.input.MouseInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.KeyTrigger;
import com.jme3.input.controls.MouseButtonTrigger;
import com.jme3.light.SpotLight;
import com.jme3.material.Material;
import com.jme3.scene.Geometry;
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
    private Node target;
    private ChaseCamera chaseCam;
    private BulletAppState bulletAppState;
    private RigidBodyControl hubPhy1;
    
    @Override
    public void simpleInitApp() {
        bulletAppState = new BulletAppState();
        stateManager.attach(bulletAppState);

        inputManager.setCursorVisible(true);

        initKeys();

        robot = new Node("Robot");
        
        HubFactory hubFactory = new HubFactory();
        Node hub1 = hubFactory.create(new Vector3f(0, 0, 0), assetManager, bulletAppState);
        robot.attachChild(hub1);
        
        Node hub2 = hubFactory.create(new Vector3f(0, 1, 0), assetManager, bulletAppState);
        robot.attachChild(hub2);
        
        Node hub3 = hubFactory.create(new Vector3f(1, 0, 0), assetManager, bulletAppState);
        robot.attachChild(hub3);
        
        Node hub4 = hubFactory.create(new Vector3f(1, 1, 0), assetManager, bulletAppState);
        robot.attachChild(hub4);
         
        setupCam(hub1);

        Geometry rootPart = (Geometry) hub1.getUserData("root");
        hubPhy1 = rootPart.getControl(RigidBodyControl.class);
        hubPhy1.setKinematic(true);

        rootPart = (Geometry) hub2.getUserData("root");
        RigidBodyControl hubPhy2 = rootPart.getControl(RigidBodyControl.class);

        rootPart = (Geometry) hub3.getUserData("root");
        RigidBodyControl hubPhy3 = rootPart.getControl(RigidBodyControl.class);
        
        rootPart = (Geometry) hub4.getUserData("root");
        RigidBodyControl hubPhy4 = rootPart.getControl(RigidBodyControl.class);
        
        SixDofJoint dof = new SixDofJoint(hubPhy1, hubPhy2, new Vector3f(0f,0.5f,0), new Vector3f(0f,-0.5f,0), false);
        dof.setAngularLowerLimit(Vector3f.ZERO);
        dof.setAngularUpperLimit(Vector3f.ZERO);
        dof.setLinearLowerLimit(Vector3f.ZERO);
        dof.setLinearUpperLimit(Vector3f.ZERO);
        dof.setCollisionBetweenLinkedBodys(false);
        bulletAppState.getPhysicsSpace().add(dof);
        
        dof = new SixDofJoint(hubPhy1, hubPhy3, new Vector3f(0.5f,0,0), new Vector3f(-0.5f,0,0), false);
        dof.setAngularLowerLimit(Vector3f.ZERO);
        dof.setAngularUpperLimit(Vector3f.ZERO);
        dof.setLinearLowerLimit(Vector3f.ZERO);
        dof.setLinearUpperLimit(Vector3f.ZERO);
        dof.setCollisionBetweenLinkedBodys(false);
        bulletAppState.getPhysicsSpace().add(dof);

        dof = new SixDofJoint(hubPhy2, hubPhy4, new Vector3f(0.5f,0,0), new Vector3f(-0.5f,0,0), false);
        dof.setAngularLowerLimit(Vector3f.ZERO);
        dof.setAngularUpperLimit(Vector3f.ZERO);
        dof.setLinearLowerLimit(Vector3f.ZERO);
        dof.setLinearUpperLimit(Vector3f.ZERO);
        dof.setCollisionBetweenLinkedBodys(false);
        bulletAppState.getPhysicsSpace().add(dof);
        
        Sphere sphere = new Sphere(30, 30, 0.25f);
        mark = new Geometry("Mark", sphere);
        Material mat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
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
    private final static String RUN = "Run";

    private void initKeys() {
        inputManager.addMapping(SELECT, new MouseButtonTrigger(MouseInput.BUTTON_LEFT));
        inputManager.addListener(actionListener, SELECT);
        inputManager.addMapping(RUN, new KeyTrigger(KeyInput.KEY_SPACE));
        inputManager.addListener(actionListener, RUN);
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
                System.out.println("----- Collisions? " + results.size() + "-----");
                if (results.size() > 0) {
                    CollisionResult closest = results.getClosestCollision();
                    System.out.println("closest: " + closest + " contact normal " + closest.getContactNormal());
                    // round the result it is not _exact_
                    System.out.println("local contact normal " + closest.getGeometry().getWorldRotation().inverse().mult(closest.getContactNormal()));

                    Vector3f pos = new Vector3f(closest.getGeometry().getWorldBound().getCenter().add(closest.getContactNormal().mult(0.5f)));
                    mark.setLocalTranslation(pos);
                    rootNode.attachChild(mark);
                    chaseCam.setSpatial(closest.getGeometry());
                } else {
                    rootNode.detachChild(mark);
                }
            } 
            else if (name.equals(RUN) && !keyPressed) {
                System.out.println("XXXXXXXXXXXXXXXXXXX");
                hubPhy1.setKinematic(false);
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
