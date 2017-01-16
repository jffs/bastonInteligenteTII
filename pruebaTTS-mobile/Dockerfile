FROM kallikrein/cordova:5.1.1

MAINTAINER jfernandez bdellacasa
RUN \
apt-get update && \
apt-get install -y lib32stdc++6 lib32z1 

# download and extract android sdk
RUN curl http://dl.google.com/android/android-sdk_r24.2-linux.tgz | tar xz -C /usr/local/
ENV ANDROID_HOME /usr/local/android-sdk-linux
ENV PATH $PATH:$ANDROID_HOME/tools:$ANDROID_HOME/platform-tools

# update and accept licences
RUN ( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | /usr/local/android-sdk-linux/tools/android update sdk --no-ui -a --filter platform-tool,build-tools-22.0.1,android-22; \
    find /usr/local/android-sdk-linux -perm 0744 | xargs chmod 755

ENV GRADLE_USER_HOME /src/gradle
VOLUME /src
WORKDIR /src
#Creo las dependencias de la app
ADD . ./
RUN node platforms.js && node plugins.js \
alias mine='sudo chown -R $USER' \
alias drun='docker run -it --rm' \
alias cordova='drun --privileged -v /dev/bus/usb:/dev/bus/usb -v $PWD:/src tallerii cordova'
