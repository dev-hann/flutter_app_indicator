part of flutter_app_indicator;

enum MenuType {
  item,
  list,
  divider,
}

extension MenuTypeExtension on MenuType {
  String get type {
    switch (this) {
      case MenuType.item:
        return 'item';
      case MenuType.list:
        return 'list';
      case MenuType.divider:
        return 'divider';
    }
  }
}
