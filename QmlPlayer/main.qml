//player state ok, but raspberry can't display.
import QtQuick 2.9
import QtQuick.Window 2.2
import QtMultimedia 5.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MediaPlayer {
        id: player
        source: "file:///home/pi/XiuZhuoYing/default.mp4"
        onError: console.log("MediaPlayer::onError:" + errorString)
        onPlaying: console.log("MediaPlayer::onPlaying")
        autoPlay: true
    }
    VideoOutput {
        anchors.fill: parent
        source: player
    }

}
