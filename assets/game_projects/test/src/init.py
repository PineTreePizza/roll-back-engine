from roll.node import Node
from roll.scene import SceneTree


class Init(Node):
    def _start(self) -> None:
        SceneTree.change_scene(
            scene_path="assets/game_projects/test/scenes/main_menu.json"
        )
