@echo off
call mvn -DskipTests clean compile

jar cvf GameNativeLibrary.jar -C target/classes .

pause