#include "Assets.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "Log.h"
#include "RendererOGL.h"
#include <rapidjson/document.h>

std::map<string, Texture> Assets::textures;
std::map<string, Shader> Assets::shaders;
std::map<string, Mesh> Assets::meshes;
std::map<string, Font> Assets::fonts;
std::map<string, string> Assets::texts;
std::map<string, Skeleton> Assets::skeletons;
std::map<string, Animation> Assets::animations;

union Vertex
{
    float f;
    uint8_t b[4];
};

Texture Assets::loadTexture(IRenderer& renderer, const string& filename, const string& name)
{
    textures[name] = loadTextureFromFile(renderer, filename.c_str());
    textures[name].setName(name);
    return textures[name];
}

Texture& Assets::getTexture(const string& name) 
{
    if (textures.find(name) == end(textures))
    {
        std::ostringstream loadError;
        loadError << "Texture " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return textures[name];
}

Shader Assets::loadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& tcShaderFile, const std::string& teShaderFile, const std::string& gShaderFile, const std::string& name)
{
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, tcShaderFile, teShaderFile, gShaderFile);
    return shaders[name];
}

Shader& Assets::getShader(const std::string& name)
{
    if (shaders.find(name) == end(shaders))
    {
        std::ostringstream loadError;
        loadError << "Shader " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return shaders[name];
}

Mesh Assets::loadMesh(const string& filename, const string& name)
{
    meshes[name] = Mesh();
    meshes[name].setName(name);
    if (loadMeshBinary(filename + ".bin", meshes[name]))
    {
        return meshes[name];
    }
    loadMeshFromFile(filename, meshes[name]);
    return meshes[name];
}

Mesh& Assets::getMesh(const std::string& name)
{
	if (meshes.find(name) == end(meshes))
    {
        std::ostringstream loadError;
        loadError << "Mesh " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return meshes[name];
}

Font Assets::loadFont(const string& filename, const string& name)
{
    fonts[name] = loadFontFromFile(filename);
    return fonts[name];
}

Font& Assets::getFont(const std::string& name)
{
    if (fonts.find(name) == end(fonts))
    {
        std::ostringstream loadError;
        loadError << "Font " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return fonts[name];
}

void Assets::loadText(const string& filename)
{
    texts.clear();
    // Try to open the file
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::ostringstream loadError;
        loadError << "Text file " << filename << " not found.";
        Log::error(LogCategory::Application, loadError.str());
        return;
    }
    // Read the entire file to a string stream
    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    // Open this file in rapidJSON
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);
    if (!doc.IsObject())
    {
        std::ostringstream loadError;
        loadError << "Text file " << filename << " is not valid JSON.";
        Log::error(LogCategory::Application, loadError.str());
        return;
    }
    // Parse the text map
    const rapidjson::Value& actions = doc["TextMap"];
    for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin(); itr != actions.MemberEnd(); ++itr)
    {
        if (itr->name.IsString() && itr->value.IsString())
        {
            texts.emplace(itr->name.GetString(), itr->value.GetString());
        }
    }
    Log::info("Loaded localization file: " + filename);

}

const string& Assets::getText(const string& key)
{
    static string errorMsg("**KEY NOT FOUND**");
    auto iter = texts.find(key);
    if (iter != end(texts))
    {
        return iter->second;
    }
    else
    {
        return errorMsg;
    }
}

Skeleton Assets::loadSkeleton(const string& filename, const string& name)
{
    skeletons[name] = loadSkeletonFromFile(filename);
    skeletons[name].setName(name);
    return skeletons[name];
}

Skeleton& Assets::getSkeleton(const std::string& name)
{
    if (skeletons.find(name) == end(skeletons))
    {
        std::ostringstream loadError;
        loadError << "Skeleton " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return skeletons[name];
}

Animation Assets::loadAnimation(const string& filename, const string& name)
{
    animations[name] = loadAnimationFromFile(filename);
    animations[name].setName(name);
    return animations[name];
}

Animation& Assets::getAnimation(const std::string& name)
{
    if (animations.find(name) == end(animations))
    {
        std::ostringstream loadError;
        loadError << "Animation " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return animations[name];
}

void Assets::clear()
{
    // Delete all textures
    for (auto iter : textures)
        iter.second.unload();
    textures.clear();
    // Delete all shaders
    for (auto iter : shaders)
        iter.second.unload();
    shaders.clear();
    // Delete all meshes
    for (auto iter : meshes)
        iter.second.unload();
    meshes.clear();
    // Delete all fonts
    for (auto iter : fonts)
        iter.second.unload();
    fonts.clear();
    // Delete texts
    texts.clear();
    // Delete all skeletons
    for (auto iter : skeletons)
        iter.second.unload();
    skeletons.clear();
    // Delete all animations
    for (auto iter : animations)
        iter.second.unload();
    animations.clear();
}

Texture Assets::loadTextureFromFile(IRenderer& renderer, const string& filename)
{
    Texture texture;
    // Not very elegant, but simpler architecture
    if (renderer.type() == IRenderer::Type::SDL)
    {
        //texture.loadSDL(dynamic_cast<RendererSDL&>(renderer), filename);
    }
    else if (renderer.type() == IRenderer::Type::OGL)
    {
        texture.loadOGL(dynamic_cast<RendererOGL&>(renderer), filename);
    }
    return texture;
}

Shader Assets::loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& tcShaderFile, const std::string& teShaderFile, const std::string& gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string tcCode;
    std::string teCode;
    std::string geometryCode;
    try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If tess control shader path is present, also load a tess control shader
        if (tcShaderFile != "") {
            std::ifstream tessControlShaderFile(tcShaderFile);
            std::stringstream tcShaderStream;
            tcShaderStream << tessControlShaderFile.rdbuf();
            tessControlShaderFile.close();
            tcCode = tcShaderStream.str();
        }
        // If tess evaluation shader path is present, also load a tess evaluation shader
        if (teShaderFile != "") {
            std::ifstream tessEvalShaderFile(teShaderFile);
            std::stringstream teShaderStream;
            teShaderStream << tessEvalShaderFile.rdbuf();
            tessEvalShaderFile.close();
            teCode = teShaderStream.str();
        }
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != "") {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::ostringstream loadError;
        std::string geomShaderFile = "";
        if (gShaderFile != "")
            geomShaderFile = gShaderFile;

        loadError << "ERROR::SHADER: Failed to read shader files " << vShaderFile << " " << fShaderFile << " "
            << geomShaderFile << "\n"
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
        Log::error(LogCategory::Render, loadError.str());
    }
    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    const GLchar* tcShaderCode = tcCode.c_str();
    const GLchar* teShaderCode = teCode.c_str();
    const GLchar* gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.compile(vShaderCode, fShaderCode,
        tcShaderFile != "" ? tcShaderCode : nullptr,
        teShaderFile != "" ? teShaderCode : nullptr,
        gShaderFile != "" ? gShaderCode : nullptr);
    return shader;
}

bool Assets::loadMeshFromFile(const string& filename, Mesh& mesh)
{
	std::ifstream file(filename);
	if (!file.is_open())
	{
		Log::error(LogCategory::Application, "File not found: Mesh " + filename);
        return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
        std::ostringstream s;
        s << "Mesh " << filename << " is not valid json";
        Log::error(LogCategory::Application, s.str());
        return false;
	}

    string shaderName = doc["shader"].GetString();
	mesh.setShaderName(shaderName);

    // Set the vertex layout/size based on the format in the file
    VertexArrayLayout layout = VertexArrayLayout::PosNormTex;
    size_t vertSize = 8;

    std::string vertexFormat = doc["vertexformat"].GetString();
    if (vertexFormat == "PosNormSkinTex")
    {
        layout = VertexArrayLayout::PosNormSkinTex;
        // This is the number of "Vertex" unions, which is 8 + 2 (for skinning)s
        vertSize = 10;
    }

	// Load textures
	const rapidjson::Value& textures = doc["textures"];
	if (!textures.IsArray() || textures.Size() < 1)
	{
        std::ostringstream s;
        s << "Mesh " << filename << " has no textures, there should be at least one";
        Log::error(LogCategory::Application, s.str());
        return false;
	}

    float specularPower = static_cast<float>(doc["specularPower"].GetDouble());
	mesh.setSpecularPower(specularPower);

    vector<string> textureNames;
	for (rapidjson::SizeType i = 0; i < textures.Size(); i++)
	{
		string texName = textures[i].GetString();
        textureNames.emplace_back(texName);
		Texture& t = getTexture(texName);
		mesh.addTexture(&t);
	}

	// Load in the vertices
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
        std::ostringstream s;
        s << "Mesh " << filename << " has no vertices";
        Log::error(LogCategory::Application, s.str());
        return false;
	}

	std::vector<Vertex> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	float radius = 0.0f;
    AABB box = AABB(Vector3::infinity, Vector3::negInfinity);
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray())
		{
            std::ostringstream s;
            s << "Unexpected vertex format for " << filename;
            Log::error(LogCategory::Application, s.str());
            return false;
		}

		Vector3 pos(static_cast<float>(vert[0].GetDouble()), static_cast<float>(vert[1].GetDouble()), static_cast<float>(vert[2].GetDouble()));
		radius = Maths::max(radius, pos.lengthSq());
        box.updateMinMax(pos);


        if (layout == VertexArrayLayout::PosNormTex)
        {
            Vertex v;
            // Add the floats
            for (rapidjson::SizeType j = 0; j < vert.Size(); j++)
            {
                v.f = static_cast<float>(vert[j].GetDouble());
                vertices.emplace_back(v);
            }
        }
        else
        {
            Vertex v;
            // Add pos/normal
            for (rapidjson::SizeType j = 0; j < 6; j++)
            {
                v.f = static_cast<float>(vert[j].GetDouble());
                vertices.emplace_back(v);
            }

            // Add skin information
            for (rapidjson::SizeType j = 6; j < 14; j += 4)
            {
                v.b[0] = vert[j].GetUint();
                v.b[1] = vert[j + 1].GetUint();
                v.b[2] = vert[j + 2].GetUint();
                v.b[3] = vert[j + 3].GetUint();
                vertices.emplace_back(v);
            }

            // Add tex coords
            for (rapidjson::SizeType j = 14; j < vert.Size(); j++)
            {
                v.f = vert[j].GetDouble();
                vertices.emplace_back(v);
            }
        }
	}

	// We were computing length squared earlier
	mesh.setRadius(Maths::sqrt(radius));
    mesh.setBox(box);

	// Load in the indices
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
        std::ostringstream s;
        s << "Mesh " << filename << " has no indices";
        Log::error(LogCategory::Application, s.str());
        return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3.0);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
            std::ostringstream s;
            s << "Invalid indices for " << filename;
            Log::error(LogCategory::Application, s.str());
            return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	// Now create a vertex array
    unsigned int nbVertices = static_cast<unsigned>(vertices.size()) / vertSize;
    unsigned int nbIndices = static_cast<unsigned int>(indices.size());
	mesh.setVertexArray(new VertexArray(vertices.data(), nbVertices, layout, indices.data(), nbIndices));
    // Save the binary mesh
    mesh.saveBinary(filename + ".bin", vertices.data(), nbVertices, layout, indices.data(), nbIndices, textureNames, box, radius, specularPower, shaderName);


    Log::info("Loaded mesh and saved binary " + filename);

	return true;
}


bool Assets::loadMeshBinary(const std::string& filename, Mesh& mesh)
{
    std::ifstream inFile(filename, std::ios::in | std::ios::binary);
    if (inFile.is_open())
    {
        // Read in header
        MeshBinHeader header;
        inFile.read(reinterpret_cast<char*>(&header), sizeof(header));

        // Validate the header signature and version
        char* sig = header.mSignature;
        if (sig[0] != 'G' || sig[1] != 'M' || sig[2] != 'S' || sig[3] != 'H' || header.version != binaryVersion)
        {
            return false;
        }

        vector<Texture*> meshTextures;
        // Read in the texture file names
        for (uint32_t i = 0; i < header.mbNbTextures; i++)
        {
            // Get the file name size
            uint16_t nameSize = 0;
            inFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));

            // Make a buffer of this size
            char* texName = new char[nameSize];
            // Read in the texture name
            inFile.read(texName, nameSize);

            // Get this texture
            Texture* t = &Assets::getTexture(texName);
            if (t == nullptr)
            {
                // If it's null, use the default texture
                t = &Assets::getTexture("Default");
            }
            meshTextures.emplace_back(t);

            delete[] texName;
        }
        mesh.setTextures(meshTextures);

        // Now read in the vertices
        unsigned vertexSize = VertexArray::getVertexSize(header.mbLayout);
        char* verts = new char[header.mbNbVertices * vertexSize];
        inFile.read(verts, header.mbNbVertices * vertexSize);

        // Now read in the indices
        uint32_t* indices = new uint32_t[header.mbNbIndices];
        inFile.read(reinterpret_cast<char*>(indices), header.mbNbIndices * sizeof(uint32_t));

        // Now create the vertex array
        mesh.setVertexArray(new VertexArray(verts, header.mbNbVertices, header.mbLayout, indices, header.mbNbIndices));

        // Cleanup memory
        delete[] verts;
        delete[] indices;

        // Set mbBox/mbRadius/specular from header
        mesh.setBox(header.mbBox);
        mesh.setRadius(header.mbRadius);
        mesh.setSpecularPower(header.mbSpecularPower);


        uint16_t shaderNameSize = 0;
        inFile.read(reinterpret_cast<char*>(&shaderNameSize), sizeof(shaderNameSize));
        char* shaderName = new char[shaderNameSize];
        inFile.read(shaderName, shaderNameSize);

        mesh.setShaderName(shaderName);


        Log::info("Loaded mesh from binary: " + filename);

        inFile.close();
        return true;
    }
    return false;
}


Font Assets::loadFontFromFile(const string& filename)
{
    vector<int> fontSizes = {
        8, 9,
        10, 11, 12, 14, 16, 18,
        20, 22, 24, 26, 28,
        30, 32, 34, 36, 38,
        40, 42, 44, 46, 48,
        52, 56,
        60, 64, 68,
        72
    };

    Font font;
    for (auto& size : fontSizes)
    {
        TTF_Font* ttfFont = TTF_OpenFont(filename.c_str(), size);
        if (ttfFont == nullptr)
        {
            std::ostringstream s;
            s << "Failed to load Font " << filename << " in size " << size;
            Log::error(LogCategory::Application, s.str());
        }
        font.addFontData(size, ttfFont);
    }
    Log::info("Loaded font " + filename);
    return font;
}

Skeleton Assets::loadSkeletonFromFile(const string& filename)
{
    Skeleton skeleton;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::ostringstream s;
        s << "File not found: Skeleton " << filename;
        Log::error(LogCategory::Application, s.str());
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    if (!doc.IsObject())
    {
        std::ostringstream s;
        s << "Skeleton " << filename << " is not valid json";
        Log::error(LogCategory::Application, s.str());
    }

    int ver = doc["version"].GetInt();

    // Check the metadata
    if (ver != 1)
    {
        std::ostringstream s;
        s << "Skeleton " << filename << " unknown format";
        Log::error(LogCategory::Application, s.str());
    }

    const rapidjson::Value& bonecount = doc["bonecount"];
    if (!bonecount.IsUint())
    {
        std::ostringstream s;
        s << "Skeleton " << filename << " doesn't have a bone count.";
        Log::error(LogCategory::Application, s.str());
    }

    size_t count = bonecount.GetUint();

    if (count > MAX_SKELETON_BONES)
    {
        std::ostringstream s;
        s << "Skeleton " << filename << " exceeds maximum bone count.";
        Log::error(LogCategory::Application, s.str());
    }

    vector<Skeleton::Bone> loadedBones;
    loadedBones.reserve(count);

    const rapidjson::Value& bones = doc["bones"];
    if (!bones.IsArray())
    {
        std::ostringstream s;
        s << "Skeleton " << filename << " doesn't have a bone array.";
        Log::error(LogCategory::Application, s.str());
    }

    if (bones.Size() != count)
    {
        std::ostringstream s;
        s << "Skeleton " << filename << " has a mismatch between the bone count and number of bones.";
        Log::error(LogCategory::Application, s.str());
    }

    Skeleton::Bone temp;

    for (rapidjson::SizeType i = 0; i < count; i++)
    {
        if (!bones[i].IsObject())
        {
            std::ostringstream s;
            s << "Skeleton " << filename << ": Bone " << i << "is invalid.";
            Log::error(LogCategory::Application, s.str());
        }

        const rapidjson::Value& name = bones[i]["name"];
        temp.name = name.GetString();

        const rapidjson::Value& parent = bones[i]["parent"];
        temp.parent = parent.GetInt();

        const rapidjson::Value& bindpose = bones[i]["bindpose"];
        if (!bindpose.IsObject())
        {
            std::ostringstream s;
            s << "Skeleton " << filename << ": Bone " << i << "is invalid.";
            Log::error(LogCategory::Application, s.str());
        }

        const rapidjson::Value& rot = bindpose["rot"];
        const rapidjson::Value& trans = bindpose["trans"];

        if (!rot.IsArray() || !trans.IsArray())
        {
            std::ostringstream s;
            s << "Skeleton " << filename << ": Bone " << i << "is invalid.";
            Log::error(LogCategory::Application, s.str());
        }

        temp.localBindPose.rotation.x = rot[0].GetDouble();
        temp.localBindPose.rotation.y = rot[1].GetDouble();
        temp.localBindPose.rotation.z = rot[2].GetDouble();
        temp.localBindPose.rotation.w = rot[3].GetDouble();

        temp.localBindPose.translation.x = trans[0].GetDouble();
        temp.localBindPose.translation.y = trans[1].GetDouble();
        temp.localBindPose.translation.z = trans[2].GetDouble();

        loadedBones.emplace_back(temp);
    }

    skeleton.setBones(loadedBones);
    skeleton.computeGlobalInvBindPose();
    Log::info("Loaded skeleton " + filename);

    return skeleton;
}

Animation Assets::loadAnimationFromFile(const string& filename)
{
    Animation animation;

    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::ostringstream s;
        s << "File not found: Animation " << filename;
        Log::error(LogCategory::Application, s.str());
    }

    std::stringstream fileStream;
    fileStream << file.rdbuf();
    std::string contents = fileStream.str();
    rapidjson::StringStream jsonStr(contents.c_str());
    rapidjson::Document doc;
    doc.ParseStream(jsonStr);

    if (!doc.IsObject())
    {
        std::ostringstream s;
        s << "Animation " << filename << " is not valid json";
        Log::error(LogCategory::Application, s.str());
    }

    int ver = doc["version"].GetInt();

    // Check the metadata
    if (ver != 1)
    {
        std::ostringstream s;
        s << "Animation " << filename << " is not valid format";
        Log::error(LogCategory::Application, s.str());
    }

    const rapidjson::Value& sequence = doc["sequence"];
    if (!sequence.IsObject())
    {
        std::ostringstream s;
        s << "Animation " << filename << " doesn't have a sequence.";
        Log::error(LogCategory::Application, s.str());
    }

    const rapidjson::Value& frames = sequence["frames"];
    const rapidjson::Value& length = sequence["length"];
    const rapidjson::Value& bonecount = sequence["bonecount"];

    if (!frames.IsUint() || !length.IsDouble() || !bonecount.IsUint())
    {
        std::ostringstream s;
        s << "Sequence " << filename << " has invalid frames, length, or bone count.";
        Log::error(LogCategory::Application, s.str());
    }

    animation.setNbFrames(frames.GetUint());
    animation.setDuration(length.GetDouble());
    animation.setNbBones(bonecount.GetUint());
    animation.setFrameDuration(animation.getDuration() / (animation.getNbFrames() - 1));

    vector<vector<BoneTransform>> animationTracks;
    animationTracks.resize(animation.getNbBones());

    const rapidjson::Value& tracks = sequence["tracks"];

    if (!tracks.IsArray())
    {
        std::ostringstream s;
        s << "Sequence " << filename << " missing a tracks array.";
        Log::error(LogCategory::Application, s.str());
    }

    for (rapidjson::SizeType i = 0; i < tracks.Size(); i++)
    {
        if (!tracks[i].IsObject())
        {
            std::ostringstream s;
            s << "Animation " << filename << ": Track element " << i << " is invalid.";
            Log::error(LogCategory::Application, s.str());
        }

        size_t boneIndex = tracks[i]["bone"].GetUint();

        const rapidjson::Value& transforms = tracks[i]["transforms"];
        if (!transforms.IsArray())
        {
            std::ostringstream s;
            s << "Animation " << filename << ": Track element " << i << " is missing transforms.";
            Log::error(LogCategory::Application, s.str());
        }

        BoneTransform temp;

        if (transforms.Size() < animation.getNbFrames())
        {
            std::ostringstream s;
            s << "Animation " << filename << ": Track element " << i << " has fewer frames than expected.";
            Log::error(LogCategory::Application, s.str());
        }

        for (rapidjson::SizeType j = 0; j < transforms.Size(); j++)
        {
            const rapidjson::Value& rot = transforms[j]["rot"];
            const rapidjson::Value& trans = transforms[j]["trans"];

            if (!rot.IsArray() || !trans.IsArray())
            {
                std::ostringstream s;
                s << "Skeleton " << filename << ": Bone " << i << " is invalid.";
                Log::error(LogCategory::Application, s.str());
            }

            temp.rotation.x = rot[0].GetDouble();
            temp.rotation.y = rot[1].GetDouble();
            temp.rotation.z = rot[2].GetDouble();
            temp.rotation.w = rot[3].GetDouble();

            temp.translation.x = trans[0].GetDouble();
            temp.translation.y = trans[1].GetDouble();
            temp.translation.z = trans[2].GetDouble();

            animationTracks[boneIndex].emplace_back(temp);
        }
    }
    animation.setTracks(animationTracks);

    Log::info("Loaded animation " + filename);
    return animation;
}
