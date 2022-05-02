
import 'dart:async';

import 'package:flutter/services.dart';

class FlutterAppIndicator {
  static const MethodChannel _channel = MethodChannel('flutter_app_indicator');

  static Future<String?> get platformVersion async {
    final String? version = await _channel.invokeMethod('getPlatformVersion');
    return version;
  }
}
