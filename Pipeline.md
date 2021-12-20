# Renderer 


### Step 1: Create Model 
1. Create data for a model, perhaps from blender. 

### Step 2: Load the Model
1. Load the data for the model.
  - Vertex position data.
  - Color data.
  - Indices.
  - Vector normals.
2. Create `DataStreams` out of the model data.

### Step 3: Define Transformations
1. Create a `Model Matrix` transformation.
2. Create a `View Matrix` transformation.
3. Create a `Projection Matrix` transformation.
4. Create a `Viewport` transformation.

### Step 4: Create a Vertex Shader
1. Load transformations as uniforms into a `Vertex Shader`.
2. Define the `code` of the vs.

### Step 5: Create a Fragment Shader
1. Load any desired uniforms into the fragment shader.
2. Define the `code` of the fragment shader.

### Step 6: Create a Shader Program
1. Combine the vertex shader and fragment shader into a shader program.

### Step 7: Execute the Pipeline
1. Pass the model data into the graphics pipeline.
  1. Vertex shader is executed.
  2. Rasterizer is run, producing fragments. 
  3. Fragment shader is executed.
  4. Fragments are drawn to the screen.


