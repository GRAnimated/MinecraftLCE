add_subdirectory(Minecraft)
add_subdirectory(Minecraft.Client)
add_subdirectory(Minecraft.Network)
add_subdirectory(Minecraft.System)
add_subdirectory(Minecraft.World)

target_sources(mcswitch PRIVATE
  main.cpp
)