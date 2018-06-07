package dai.android.ffmpeg.player;

public class NativePlayer {

    public static native int playVideo(String url, Object surface);
}
