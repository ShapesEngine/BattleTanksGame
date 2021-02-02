cmake_minimum_required( VERSION 3.13 FATAL_ERROR )

set( PROJECT_NAME BattleTanks )

project( ${PROJECT_NAME} )

add_executable( ${PROJECT_NAME} 
				src/main.cpp

				src/Renderer/ShaderProgram.cpp
				src/Renderer/ShaderProgram.h 
				src/Renderer/Texture2D.cpp
				src/Renderer/Texture2D.h 
				src/Renderer/Sprite.cpp 
				src/Renderer/Sprite.h 	
				src/Renderer/Renderer.cpp 
				src/Renderer/Renderer.h 	
				src/Renderer/SpriteAnimator.cpp 
				src/Renderer/SpriteAnimator.h 

				src/Resources/ResourceManager.cpp 
				src/Resources/ResourceManager.h 
				src/Resources/stb_image.h 

				src/Physics/PhysicsEngine.cpp 
				src/Physics/PhysicsEngine.h 

				src/System/Utils/ShaderHelper.cpp
				src/System/Utils/ShaderHelper.h	
				src/System/Utils/VertexBuffer.cpp 
				src/System/Utils/VertexBuffer.h 
				src/System/Utils/IndexBuffer.cpp 
				src/System/Utils/IndexBuffer.h 
				src/System/Utils/VertexBufferLayout.cpp 
				src/System/Utils/VertexBufferLayout.h 
				src/System/Utils/VertexArray.cpp 
				src/System/Utils/VertexArray.h 
				src/System/Timer.cpp
				src/System/Timer.h
				
				src/Game/Game.h				
				src/Game/Game.cpp	
				src/Game/Level.h				
				src/Game/Level.cpp

				src/Game/GameObjects/Tank.h				
				src/Game/GameObjects/Tank.cpp
				src/Game/GameObjects/IGameObject.h				
				src/Game/GameObjects/IGameObject.cpp
				src/Game/GameObjects/BrickWall.h				
				src/Game/GameObjects/BrickWall.cpp
				src/Game/GameObjects/ConcreteWall.h				
				src/Game/GameObjects/ConcreteWall.cpp
				src/Game/GameObjects/Trees.h				
				src/Game/GameObjects/Trees.cpp
				src/Game/GameObjects/Ice.h				
				src/Game/GameObjects/Ice.cpp
				src/Game/GameObjects/Water.h				
				src/Game/GameObjects/Water.cpp
				src/Game/GameObjects/Eagle.h				
				src/Game/GameObjects/Eagle.cpp
				src/Game/GameObjects/Border.h				
				src/Game/GameObjects/Border.cpp
				src/Game/GameObjects/Bullet.h				
				src/Game/GameObjects/Bullet.cpp

				res/resources.json
				res/shaders/sprite.vert
				res/shaders/sprite.frag
			  )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
				
target_compile_features( ${PROJECT_NAME} PUBLIC cxx_std_17 ) 

set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL "" FORCE )

add_subdirectory( external/glfw )
target_link_libraries( ${PROJECT_NAME} glfw )

add_subdirectory( external/glad )
target_link_libraries( ${PROJECT_NAME} glad )

include_directories( external/glm )

include_directories( external/rapidjson )

set_target_properties( ${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ )

add_custom_command( TARGET ${PROJECT_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res )