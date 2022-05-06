import 'dart:async';

import 'package:flutter/material.dart';

import 'package:flutter_app_indicator/flutter_app_indicator.dart';

void main() {
  runApp(const MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({Key? key}) : super(key: key);

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final FlutterAppIndicator _indicator = FlutterAppIndicator();
  Timer? _timer;
  @override
  void initState() {
    super.initState();
    init();
  }

  void init() async {
    print("init Indicator");
    await _indicator.init(
      title: "TestTitle",
      label: "TestLabel",
      iconPath: "assets/sleep.png",
    );
    print("init Menu");
    await _indicator.setMenu(
      [
        MenuItem("Hello1j", () {}),
        MenuSeparator(),
        MenuItem("Hello2", () {}),
      ],
    );
    initTimer();
  }

  void initTimer() {
    if (_timer != null && _timer!.isActive) {
      _timer!.cancel();
    }
    _timer = Timer.periodic(Duration(seconds: 1), (_t) {
      final s = _t.tick;
      if (s.isOdd) {
        _indicator.setIcon("assets/sleep.png");
      } else {
        _indicator.setIcon("assets/app_icon.png");
      }
      _indicator.setLabel("TestLabel$s");
    });
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: Center(
          child: Text('Hello Flutter'),
        ),
      ),
    );
  }
}
