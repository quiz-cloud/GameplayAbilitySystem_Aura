在虚幻引擎（Unreal Engine）的C++编程规范中，类名前缀代表了该类的继承体系和引擎内部的垃圾回收/反射机制：

## **A** - Actor 类
**代表**：继承自 `AActor` 的类，是可以放入关卡（Level）中的实体对象。

**特点**：
- 拥有变换（Transform）属性（位置、旋转、缩放）
- 支持网络复制（Replication）
- 可以被销毁（Destroy）

**典型例子**：
- `ACharacter` - 角色基类
- `AGameMode` / `AGameModeBase` - 游戏模式
- `APlayerController` - 玩家控制器
- `APawn` - 可被控制的棋子单位
- `AStaticMeshActor` - 静态网格体Actor

## **U** - UObject 类
**代表**：继承自 `UObject` 的类，是UE对象系统的基类。

**特点**：
- 支持垃圾回收（Garbage Collection）
- 支持反射系统（用于蓝图交互、序列化）
- **不能**直接放入关卡，通常作为组件或数据资源存在

**典型例子**：
- `UActorComponent` - Actor组件基类（如 `UStaticMeshComponent`）
- `USceneComponent` - 场景组件（有Transform）
- `UGameInstance` - 游戏实例（跨关卡持久）
- `UDataAsset` - 数据资源
- `UUserWidget` - UMG界面控件
- `USkeletalMesh` - 骨骼网格资源

## **F** - 结构体 / 非UObject 类
**代表**：普通C++结构体（`struct`）或不继承UObject的类。

**特点**：
- 不具备UObject的反射和垃圾回收机制
- 通常用于数据传递、数学计算、临时结构
- 需要手动管理内存

**典型例子**：
- `FVector` / `FVector3f` - 三维向量
- `FRotator` / `FQuat` - 旋转/四元数
- `FTransform` - 变换矩阵
- `FString` / `FText` / `FName` - 字符串类型
- `FLinearColor` / `FColor` - 颜色结构
- `FHitResult` - 射线检测命中结果

---

## 其他常见前缀

| 前缀 | 含义 | 例子 |
|------|------|------|
| **I** | 接口类（Interface） | `IInputDevice`, `IOnlineSubsystem` |
| **E** | 枚举（Enum） | `EEngineMode`, `ELevelTick` |
| **T** | 模板类（Template） | `TArray<T>`, `TMap<K,V>`, `TSharedPtr<T>` |
| **S** | Slate UI 类 | `SButton`, `SWidget` |
| **U**+**I** | UInterface（蓝图接口） | `UBlueprintable` |

## 记忆技巧

- **A** = **A**ctor = 世界中的"演员"（实体）
- **U** = **U**Object = 引擎管理的"东西"（资源/组件）
- **F** = **F**loat/Struct最初的设计，现在泛指**F**oundation（基础数据类型）

遵循这些命名规范能让引擎的**UHT（Unreal Header Tool）**正确识别类类型，生成反射数据，确保蓝图可访问性和垃圾回收正常工作。
