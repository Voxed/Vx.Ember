# Vx.Ember

## Description

Vx.Ember is meant to be a simple and modular rendering engine.
The renderer is SceneGraph based in order to allow for contextual rendering.

Each rendering pass, such as a PBR or AO access this SceneGraph through a
visitor interface. For custom external node-types an OtherNode interface 
can be used along with a getOtherNodeType() method to allow for forking 
off into custom visitors.

Speed will not be the main focus of this rendering engine, features and
ease of use will be at top of mind. However, faster methods will always be
prioritized if there are no drawbacks.

## Source tree

The idealized source tree should look something like this, note that this
is not the actual source tree, only how I plan it to look.

Passes will be single units hooked into the core ember instance. These will
then be invoked whenever the engine is updated, and it's up to them to 
instantiate and accept their corresponding visitors. Pass dependencies are
done as with any aggregate hierarchy, just pass necessary pass instances to
the next pass in its constructor. 
```
source/
├─ Ember.h
├─ passes/
│  ├─ Pass.h
│  ├─ AOPass.h
│  ├─ PBRPass.h
├─ visitors/
│  ├─ nodes/
│  │  ├─ CameraNode.h
│  │  ├─ OtherNode.h
│  │  ├─ GeometryNode.h
│  ├─ Visitor.h
│  ├─ AOVisitor.h
│  ├─ PBRVisitor.h
```

## Example

Again, this is just an idealized example of how the engine might be used.

```c++
int main() {
    Ember ember;
    
    DepthPass depthPass; // Depth pass does not need any pass dependency.
    AOPass aoPass(&depthPass); // AO pass only has access to the depth texture.
    PBRPass pbrPass(&aoPass); // PBR pass only has access to the pbr texture.
    
    ember.addPass(depthPass);
    ember.addPass(aoPass);
    ember.addPass(pbrPass);
    
    // ... Load mesh
    
    GeometryNode geoNode(mesh);
    
    ember.root().addChild(geoNode); // Add mesh node to SceneGraph.
    
    // ... GL init code
    
    while(running) {
        ember.render();
        
        // ... Present code
    }
}
```