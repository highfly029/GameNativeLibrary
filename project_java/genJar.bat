@echo off
mvn clean compile

jar cvf GameNativeLibrary.jar -C target/classes .
pause