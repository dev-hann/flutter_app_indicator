part of flutter_app_indicator;

enum MenuType {
  item,
  list,
  divider,
}

abstract class MenuItemBase {
  final String name;
  final MenuType type;

  MenuItemBase(this.name, this.type);
}

class MenuItem extends MenuItemBase {
  MenuItem(
    String name,
    this.onTap,
  ) : super(name, MenuType.item);

  final Function() onTap;
}

class MenuItemList extends MenuItemBase {
  MenuItemList(
    String name,
    this.itemList,
  ) : super(name, MenuType.list);
  final List<MenuItemBase> itemList;
}

class MenuSeparator extends MenuItemBase {
  MenuSeparator()
      : super(
          MenuType.divider.toString(),
          MenuType.divider,
        );
}
