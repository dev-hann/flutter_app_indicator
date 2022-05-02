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
  @override
  void initState() {
    super.initState();
    _indicator.init(
      title: "TestTitle",
      label: "TestLabel",
      iconPath: "assets/sleep.png",
      menuList: [],
    );
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
