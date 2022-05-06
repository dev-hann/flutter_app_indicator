part of flutter_app_indicator;

abstract class MenuItemBase {
  final String? name;
  final int typeIndex;
  MenuType get type => MenuType.values[typeIndex];

  MenuItemBase(this.name, this.typeIndex);
  Map<String, dynamic> toMap() {
    return {
      'name': name,
      'typeIndex': typeIndex,
      'hashCode': hashCode,
    };
  }
}

class MenuItem extends MenuItemBase {
  MenuItem(
    String name,
    this.onTap,
  ) : super(name, MenuType.item.index);

  final Function() onTap;

  // @override
  // Map<String, dynamic> toMap() {
  //   final _res = super.toMap();
  //   _res['onTap'] = onTap();
  //   return _res;
  // }
}

class MenuItemList extends MenuItemBase {
  MenuItemList(
    String name,
    this.itemList,
  ) : super(name, MenuType.list.index);
  final List<MenuItemBase> itemList;

  @override
  Map<String, dynamic> toMap() {
    final _res = super.toMap();
    _res['itemList'] = itemList.map((e) => e.toMap()).toList();
    return _res;
  }
}

class MenuSeparator extends MenuItemBase {
  MenuSeparator()
      : super(
          null,
          MenuType.divider.index,
        );
}
