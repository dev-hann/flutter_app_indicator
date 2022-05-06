library flutter_app_indicator;

import 'dart:async';
import 'dart:io';

import 'package:flutter/services.dart';
import 'package:flutter/widgets.dart';
import 'package:path/path.dart';

part 'menu_item.dart';
part 'menu_type.dart';

const _channelKey = 'flutter_app_indicator';

const _initKey = 'init';
const _iconKey = 'icon';
const _labelKey = 'label';
const _titleKey = 'title';
const _menuKey = 'menu';

class FlutterAppIndicator {
  static final FlutterAppIndicator _instance = FlutterAppIndicator._internal();
  factory FlutterAppIndicator() {
    return _instance;
  }
  FlutterAppIndicator._internal();

  final MethodChannel _channel = const MethodChannel(_channelKey);

  bool _hasListener = false;

  void _initChannelListener() {
    if (_hasListener) return;
    _channel.setMethodCallHandler((method) async {
      final _method = method.method;
      print(_method);
    });
    _hasListener = true;
  }

  Future<bool> init({
    required String title,
    required String iconPath,
    required String label,
  }) async {
    _initChannelListener();
    return await _channel.invokeMethod(
      _initKey,
      {
        'title': title,
        'iconPath': _fullPath(iconPath),
        'label': label,
      },
    );
  }

  Future<bool> setIcon(String iconPath) async {
    return await _channel.invokeMethod(_iconKey, {
      'iconPath': _fullPath(iconPath),
    });
  }

  Future<bool> setLabel(String label) async {
    return await _channel.invokeMethod(_labelKey, {
      'label': label,
    });
  }

  Future<bool> setTitle(String title) async {
    return await _channel.invokeMethod(_titleKey, {
      'title': title,
    });
  }

  final Map<int, VoidCallback> _callbackMap = {};
  Future<bool> setMenu(List<MenuItemBase> menuList) async {
    _parseCallback(menuList);
    return await _channel.invokeMethod(_menuKey, _itemList(menuList));
  }

  void _parseCallback(List<MenuItemBase> menuList) {
    for (final item in menuList) {
      switch (item.type) {
        case MenuType.item:
          final MenuItem _item = item as MenuItem;
          _callbackMap[item.hashCode] = _item.onTap;
          break;
        case MenuType.list:
          final MenuItemList _list = item as MenuItemList;
          _parseCallback(_list.itemList);
          break;
        case MenuType.divider:
          break;
      }
    }
  }

  List<Map<String, dynamic>> _itemList(List<MenuItemBase> list) {
    return list.map((e) => e.toMap()).toList();
  }

  String _fullPath(String path) {
    return joinAll([
      dirname(Platform.resolvedExecutable),
      'data/flutter_assets/',
      path,
    ]);
  }
}
