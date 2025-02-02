import roll_engine_api
from roll.math import Rect2
from roll.node import CollisionShape2D


class Test(CollisionShape2D):
    @classmethod
    def new(cls):
        return roll_engine_api.node_new(
            class_path=f"{__name__}",
            class_name=f"{__class__.__name__}",
            node_type=f"{cls.extract_valid_inheritance_node()}",
        )

    def _start(self) -> None:
        self.collider_rect = Rect2(x=300, y=300, w=40, h=40)
        print(f"Start called! Rect = {self.collider_rect}")

    def _physics_process(self, delta_time: float) -> None:
        # print("Process!")
        pass
