library flutter_app_indicator;

import 'dart:async';
import 'dart:io';

import 'package:flutter/services.dart';
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

  Future init({
    required String title,
    required String iconPath,
    required String label,
  }) async {
    final _res = await _channel.invokeMethod(
      _initKey,
      {
        'title': title,
        'iconPath': _fullPath(iconPath),
        'label': label,
      },
    );
    print(_res);
  }

  Future setIcon(String iconPath) async {
    _channel.invokeMethod(_iconKey, {
      'iconPath': _fullPath(iconPath),
    });
  }

  Future setLabel(String label) async {
    final _res = await _channel.invokeMethod(_labelKey, {
      'label': label,
    });
    return _res;
  }

  Future setTitle(String title) async {
    _channel.invokeMethod(_titleKey, {
      'title': title,
    });
  }

  Future setMenu(List<MenuItemBase> menuList) async {
    final _res = await _channel.invokeMethod(_menuKey, _itemList(menuList));
    print(_res);
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
