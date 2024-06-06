<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Debug|x64">
      <Configuration>Debug</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64">
      <Configuration>Release</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <VCProjectVersion>16.0</VCProjectVersion>
    <ProjectGuid>{e196c9d3-5728-4917-a35f-654b927274c9}</ProjectGuid>
    <RootNamespace>RacingGame</RootNamespace>
    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="Shared">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <LinkIncremental>true</LinkIncremental>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <IncludePath>$(SolutionDir)Externals\rapidjson\include;$(SolutionDir)Externals\SDL2_image-2.6.3\include;$(SolutionDir)Externals\SDL2_mixer-2.6.3\include;$(SolutionDir)Externals\SDL2_ttf-2.20.2\include;$(SolutionDir)Externals\glew-2.1.0\include;$(SolutionDir)Externals\SDL2-2.28.5\include;$(IncludePath)</IncludePath>
    <LibraryPath>$(SolutionDir)Externals\SDL2_image-2.6.3\lib\x64;$(SolutionDir)Externals\SDL2_mixer-2.6.3\lib\x64;$(SolutionDir)Externals\SDL2_ttf-2.20.2\lib\x64;$(SolutionDir)Externals\glew-2.1.0\lib\Release\x64;$(SolutionDir)Externals\SDL2-2.28.5\lib\x64;$(LibraryPath)</LibraryPath>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalDependencies>SDL2.lib;SDL2main.lib;SDL2_image.lib;SDL2_mixer.lib;SDL2_ttf.lib;opengl32.lib;glew32.lib;fmodL64_vc.lib;fmodstudioL64_vc.lib;%(AdditionalDependencies)</AdditionalDependencies>
    </Link>
    <PostBuildEvent>
      <Command>xcopy "$(ProjectDir)Res" "$(TargetDir)Res" /e /y /i /r</Command>
    </PostBuildEvent>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <LanguageStandard>stdcpp20</LanguageStandard>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Include="AABB.cpp" />
    <ClCompile Include="Actor.cpp" />
    <ClCompile Include="Animation.cpp" />
    <ClCompile Include="AnimSpriteComponent.cpp" />
    <ClCompile Include="BackgroundSpriteComponent.cpp" />
    <ClCompile Include="BallActor.cpp" />
    <ClCompile Include="BallMoveComponent.cpp" />
    <ClCompile Include="BoneTransform.cpp" />
    <ClCompile Include="BoxComponent.cpp" />
    <ClCompile Include="Button.cpp" />
    <ClCompile Include="CameraComponent.cpp" />
    <ClCompile Include="Collisions.cpp" />
    <ClCompile Include="DialogBox.cpp" />
    <ClCompile Include="FollowActor.cpp" />
    <ClCompile Include="FollowCameraComponent.cpp" />
    <ClCompile Include="Font.cpp" />
    <ClCompile Include="FPSCameraComponent.cpp" />
    <ClCompile Include="CircleCollisionComponent.cpp" />
    <ClCompile Include="Component.cpp" />
    <ClCompile Include="ControllerState.cpp" />
    <ClCompile Include="CubeActor.cpp" />
    <ClCompile Include="FPSActor.cpp" />
    <ClCompile Include="Game.cpp" />
    <ClCompile Include="GBuffer.cpp" />
    <ClCompile Include="HUD.cpp" />
    <ClCompile Include="InputComponent.cpp" />
    <ClCompile Include="InputSystem.cpp" />
    <ClCompile Include="KeyboardState.cpp" />
    <ClCompile Include="LevelLoader.cpp" />
    <ClCompile Include="LineSegment.cpp" />
    <ClCompile Include="Log.cpp" />
    <ClCompile Include="Main.cpp" />
    <ClCompile Include="Matrix4.cpp" />
    <ClCompile Include="Mesh.cpp" />
    <ClCompile Include="MeshComponent.cpp" />
    <ClCompile Include="MirrorCameraComponent.cpp" />
    <ClCompile Include="MouseState.cpp" />
    <ClCompile Include="MoveComponent.cpp" />
    <ClCompile Include="OrbitActor.cpp" />
    <ClCompile Include="OrbitCameraComponent.cpp" />
    <ClCompile Include="PauseScreen.cpp" />
    <ClCompile Include="PhysicsSystem.cpp" />
    <ClCompile Include="Plane.cpp" />
    <ClCompile Include="PlaneActor.cpp" />
    <ClCompile Include="PointLightComponent.cpp" />
    <ClCompile Include="Quaternion.cpp" />
    <ClCompile Include="Random.cpp" />
    <ClCompile Include="Rectangle.cpp" />
    <ClCompile Include="RendererOGL.cpp" />
    <ClCompile Include="Assets.cpp" />
    <ClCompile Include="Shader.cpp" />
    <ClCompile Include="SkeletalMeshComponent.cpp" />
    <ClCompile Include="Skeleton.cpp" />
    <ClCompile Include="Sphere.cpp" />
    <ClCompile Include="SphereActor.cpp" />
    <ClCompile Include="Spline.cpp" />
    <ClCompile Include="SplineActor.cpp" />
    <ClCompile Include="SplineCameraComponent.cpp" />
    <ClCompile Include="SpriteComponent.cpp" />
    <ClCompile Include="TargetActor.cpp" />
    <ClCompile Include="TargetComponent.cpp" />
    <ClCompile Include="Texture.cpp" />
    <ClCompile Include="Timer.cpp" />
    <ClCompile Include="UIScreen.cpp" />
    <ClCompile Include="Vector2.cpp" />
    <ClCompile Include="Vector3.cpp" />
    <ClCompile Include="VertexArray.cpp" />
    <ClCompile Include="Window.cpp" />
  </ItemGroup>
  <ItemGroup>
    <ClInclude Include="AABB.h" />
    <ClInclude Include="Actor.h" />
    <ClInclude Include="Animation.h" />
    <ClInclude Include="AnimSpriteComponent.h" />
    <ClInclude Include="Assets.h" />
    <ClInclude Include="BackgroundSpriteComponent.h" />
    <ClInclude Include="BallActor.h" />
    <ClInclude Include="BallMoveComponent.h" />
    <ClInclude Include="BoneTransform.h" />
    <ClInclude Include="BoxComponent.h" />
    <ClInclude Include="Button.h" />
    <ClInclude Include="CameraComponent.h" />
    <ClInclude Include="Collisions.h" />
    <ClInclude Include="Color.h" />
    <ClInclude Include="DialogBox.h" />
    <ClInclude Include="FollowActor.h" />
    <ClInclude Include="FollowCameraComponent.h" />
    <ClInclude Include="Font.h" />
    <ClInclude Include="FPSCameraComponent.h" />
    <ClInclude Include="CircleCollisionComponent.h" />
    <ClInclude Include="Component.h" />
    <ClInclude Include="ControllerState.h" />
    <ClInclude Include="CubeActor.h" />
    <ClInclude Include="DirectionalLight.h" />
    <ClInclude Include="FPSActor.h" />
    <ClInclude Include="Game.h" />
    <ClInclude Include="GBuffer.h" />
    <ClInclude Include="HUD.h" />
    <ClInclude Include="InputComponent.h" />
    <ClInclude Include="InputSystem.h" />
    <ClInclude Include="IRenderer.h" />
    <ClInclude Include="KeyboardState.h" />
    <ClInclude Include="LevelLoader.h" />
    <ClInclude Include="LineSegment.h" />
    <ClInclude Include="Log.h" />
    <ClInclude Include="Maths.h" />
    <ClInclude Include="Matrix4.h" />
    <ClInclude Include="MatrixPalette.h" />
    <ClInclude Include="Mesh.h" />
    <ClInclude Include="MeshComponent.h" />
    <ClInclude Include="MirrorCameraComponent.h" />
    <ClInclude Include="MouseState.h" />
    <ClInclude Include="MoveComponent.h" />
    <ClInclude Include="OrbitActor.h" />
    <ClInclude Include="OrbitCameraComponent.h" />
    <ClInclude Include="PauseScreen.h" />
    <ClInclude Include="PhysicsSystem.h" />
    <ClInclude Include="Plane.h" />
    <ClInclude Include="PlaneActor.h" />
    <ClInclude Include="PointLightComponent.h" />
    <ClInclude Include="Quaternion.h" />
    <ClInclude Include="Random.h" />
    <ClInclude Include="Rectangle.h" />
    <ClInclude Include="RendererOGL.h" />
    <ClInclude Include="Assets.h" />
    <ClInclude Include="Shader.h" />
    <ClInclude Include="SkeletalMeshComponent.h" />
    <ClInclude Include="Skeleton.h" />
    <ClInclude Include="Sphere.h" />
    <ClInclude Include="SphereActor.h" />
    <ClInclude Include="Spline.h" />
    <ClInclude Include="SplineActor.h" />
    <ClInclude Include="SplineCameraComponent.h" />
    <ClInclude Include="SpriteComponent.h" />
    <ClInclude Include="TargetActor.h" />
    <ClInclude Include="TargetComponent.h" />
    <ClInclude Include="Texture.h" />
    <ClInclude Include="Timer.h" />
    <ClInclude Include="UIScreen.h" />
    <ClInclude Include="Vector2.h" />
    <ClInclude Include="Vector3.h" />
    <ClInclude Include="VertexArray.h" />
    <ClInclude Include="Window.h" />
  </ItemGroup>
  <ItemGroup>
    <Content Include="..\Assets\Res_005-011\Astroid.png" />
    <Content Include="..\Assets\Res_005-011\Enemy01.png" />
    <Content Include="..\Assets\Res_005-011\Enemy02.png" />
    <Content Include="..\Assets\Res_005-011\Enemy03.png" />
    <Content Include="..\Assets\Res_005-011\Enemy04.png" />
    <Content Include="..\Assets\Res_005-011\Enemy05.png" />
    <Content Include="..\Assets\Res_005-011\Enemy06.png" />
    <Content Include="..\Assets\Res_005-011\Farback01.png" />
    <Content Include="..\Assets\Res_005-011\Farback02.png" />
    <Content Include="..\Assets\Res_005-011\Laser.png" />
    <Content Include="..\Assets\Res_005-011\Ship.png" />
    <Content Include="..\Assets\Res_005-011\Ship01.png" />
    <Content Include="..\Assets\Res_005-011\Ship02.png" />
    <Content Include="..\Assets\Res_005-011\Ship03.png" />
    <Content Include="..\Assets\Res_005-011\Ship04.png" />
    <Content Include="..\Assets\Res_005-011\ShipWithThrust.png" />
    <Content Include="..\Assets\Res_005-011\Stars.png" />
    <Content Include="..\Assets\Res_012-015\Airplane.png" />
    <Content Include="..\Assets\Res_012-015\Base.png" />
    <Content Include="..\Assets\Res_012-015\Missile.png" />
    <Content Include="..\Assets\Res_012-015\Projectile.png" />
    <Content Include="..\Assets\Res_012-015\TileBrown.png" />
    <Content Include="..\Assets\Res_012-015\TileBrownSelected.png" />
    <Content Include="..\Assets\Res_012-015\TileGreen.png" />
    <Content Include="..\Assets\Res_012-015\TileGreenSelected.png" />
    <Content Include="..\Assets\Res_012-015\TileGrey.png" />
    <Content Include="..\Assets\Res_012-015\TileGreySelected.png" />
    <Content Include="..\Assets\Res_012-015\TileRed.png" />
    <Content Include="..\Assets\Res_012-015\TileRedSelected.png" />
    <Content Include="..\Assets\Res_012-015\TileTan.png" />
    <Content Include="..\Assets\Res_012-015\TileTanSelected.png" />
    <Content Include="..\Assets\Res_012-015\Tower.png" />
    <Content Include="..\Assets\Res_016-025\Meshes\Cube.gpmesh" />
    <Content Include="..\Assets\Res_016-025\Meshes\Plane.gpmesh" />
    <Content Include="..\Assets\Res_016-025\Meshes\RacingCar.gpmesh" />
    <Content Include="..\Assets\Res_016-025\Meshes\Rifle.gpmesh" />
    <Content Include="..\Assets\Res_016-025\Meshes\Sphere.gpmesh" />
    <Content Include="..\Assets\Res_016-025\Meshes\Target.gpmesh" />
    <Content Include="..\Assets\Res_016-025\Shaders\BasicMesh.frag" />
    <Content Include="..\Assets\Res_016-025\Shaders\BasicMesh.vert" />
    <Content Include="..\Assets\Res_016-025\Shaders\Phong.frag" />
    <Content Include="..\Assets\Res_016-025\Shaders\Phong.vert" />
    <Content Include="..\Assets\Res_016-025\Shaders\Sprite.frag" />
    <Content Include="..\Assets\Res_016-025\Shaders\Sprite.vert" />
    <Content Include="..\Assets\Res_016-025\Textures\Crosshair.png" />
    <Content Include="..\Assets\Res_016-025\Textures\Cube.png" />
    <Content Include="..\Assets\Res_016-025\Textures\Default.png" />
    <Content Include="..\Assets\Res_016-025\Textures\ha.png" />
    <Content Include="..\Assets\Res_016-025\Textures\HealthBar.png" />
    <Content Include="..\Assets\Res_016-025\Textures\Plane.png" />
    <Content Include="..\Assets\Res_016-025\Textures\RacingCar.png" />
    <Content Include="..\Assets\Res_016-025\Textures\Radar.png" />
    <Content Include="..\Assets\Res_016-025\Textures\Rifle.png" />
    <Content Include="..\Assets\Res_016-025\Textures\Sphere.png" />
    <Content Include="..\Assets\Res_016-025\Textures\Target.png" />
    <Content Include="..\Assets\Res_036-042\.DS_Store" />
    <Content Include="..\Assets\Res_036-042\Fonts\Carlito-Regular.ttf" />
    <Content Include="..\Assets\Res_036-042\Fonts\feet.ttf" />
    <Content Include="..\Assets\Res_036-042\Localization\English.gptext" />
    <Content Include="..\Assets\Res_036-042\Localization\Russian.gptext" />
    <Content Include="..\Assets\Res_036-042\Textures\Arrow.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Blip.png" />
    <Content Include="..\Assets\Res_036-042\Textures\BlipDown.png" />
    <Content Include="..\Assets\Res_036-042\Textures\BlipUp.png" />
    <Content Include="..\Assets\Res_036-042\Textures\ButtonBlue.png" />
    <Content Include="..\Assets\Res_036-042\Textures\ButtonYellow.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Crosshair.png" />
    <Content Include="..\Assets\Res_036-042\Textures\CrosshairGreen.png" />
    <Content Include="..\Assets\Res_036-042\Textures\CrosshairRed.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Cube.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Default.png" />
    <Content Include="..\Assets\Res_036-042\Textures\DialogBG.png" />
    <Content Include="..\Assets\Res_036-042\Textures\HealthBar.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Plane.png" />
    <Content Include="..\Assets\Res_036-042\Textures\RacingCar.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Radar.png" />
    <Content Include="..\Assets\Res_036-042\Textures\RadarArrow.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Rifle.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Sphere.png" />
    <Content Include="..\Assets\Res_036-042\Textures\Target.png" />
    <Content Include="..\Assets\Res_043-044\.DS_Store" />
    <Content Include="..\Assets\Res_043-044\Animations\CatActionIdle.gpanim" />
    <Content Include="..\Assets\Res_043-044\Animations\CatRunMOBA.gpanim" />
    <Content Include="..\Assets\Res_043-044\Animations\CatRunSprint.gpanim" />
    <Content Include="..\Assets\Res_043-044\Animations\CatWarrior.gpskel" />
    <Content Include="..\Assets\Res_043-044\Fonts\Carlito-Regular.ttf" />
    <Content Include="..\Assets\Res_043-044\Localization\English.gptext" />
    <Content Include="..\Assets\Res_043-044\Localization\Russian.gptext" />
    <Content Include="..\Assets\Res_043-044\Meshes\CatWarrior.gpmesh" />
    <Content Include="..\Assets\Res_043-044\Meshes\Cube.gpmesh" />
    <Content Include="..\Assets\Res_043-044\Meshes\Plane.gpmesh" />
    <Content Include="..\Assets\Res_043-044\Meshes\RacingCar.gpmesh" />
    <Content Include="..\Assets\Res_043-044\Meshes\Rifle.gpmesh" />
    <Content Include="..\Assets\Res_043-044\Meshes\Sphere.gpmesh" />
    <Content Include="..\Assets\Res_043-044\Meshes\Target.gpmesh" />
    <Content Include="..\Assets\Res_043-044\Shaders\BasicMesh.frag" />
    <Content Include="..\Assets\Res_043-044\Shaders\BasicMesh.vert" />
    <Content Include="..\Assets\Res_043-044\Shaders\Phong.frag" />
    <Content Include="..\Assets\Res_043-044\Shaders\Phong.vert" />
    <Content Include="..\Assets\Res_043-044\Shaders\Skinned.vert" />
    <Content Include="..\Assets\Res_043-044\Shaders\Sprite.frag" />
    <Content Include="..\Assets\Res_043-044\Shaders\Sprite.vert" />
    <Content Include="..\Assets\Res_043-044\Textures\Arrow.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Blip.png" />
    <Content Include="..\Assets\Res_043-044\Textures\BlipDown.png" />
    <Content Include="..\Assets\Res_043-044\Textures\BlipUp.png" />
    <Content Include="..\Assets\Res_043-044\Textures\ButtonBlue.png" />
    <Content Include="..\Assets\Res_043-044\Textures\ButtonYellow.png" />
    <Content Include="..\Assets\Res_043-044\Textures\CatWarrior.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Crosshair.png" />
    <Content Include="..\Assets\Res_043-044\Textures\CrosshairGreen.png" />
    <Content Include="..\Assets\Res_043-044\Textures\CrosshairRed.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Cube.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Default.png" />
    <Content Include="..\Assets\Res_043-044\Textures\DialogBG.png" />
    <Content Include="..\Assets\Res_043-044\Textures\HealthBar.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Plane.png" />
    <Content Include="..\Assets\Res_043-044\Textures\RacingCar.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Radar.png" />
    <Content Include="..\Assets\Res_043-044\Textures\RadarArrow.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Rifle.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Sphere.png" />
    <Content Include="..\Assets\Res_043-044\Textures\Target.png" />
    <Content Include="NewFile1.md" />
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
  <ProjectExtensions>
    <VisualStudio>
      <UserProperties />
    </VisualStudio>
  </ProjectExtensions>
</Project>