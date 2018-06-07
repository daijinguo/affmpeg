package dai.android.ffmpeg.V;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import dai.android.ffmpeg.R;
import dai.android.ffmpeg.player.NativePlayer;

public class SimpleLiveActivity extends AppCompatActivity implements SurfaceHolder.Callback {

    private SurfaceHolder mSurfaceHolder;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_simple_live);

        SurfaceView surfaceView = findViewById(R.id.ViewSurface);
        mSurfaceHolder = surfaceView.getHolder();
        mSurfaceHolder.addCallback(this);
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        new Thread(new Runnable() {
            @Override
            public void run() {

                // the webaddress
                // 1. https://blog.csdn.net/robinson_911/article/details/78805200

                //香港卫视：http://live.hkstv.hk.lxdns.com/live/hks/playlist.m3u8
                //CCTV1高清 ：http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8
                //CCTV3高清 ：http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8
                //CCTV5高清 ：http://ivi.bupt.edu.cn/hls/cctv5hd.m3u8
                //CCTV5+高清：http://ivi.bupt.edu.cn/hls/cctv5phd.m3u8
                //CCTV6高清 ：http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8
                //苹果提供的测试源（点播）：http://devimages.apple.com.edgekey.net/streaming/examples/bipbop_4x3/gear2/prog_index.m3u8

                //String strUrl = "http://tanzi27niu.cdsb.mobi/wps/wp-content/uploads/2017/05/2017-05-17_17-33-30.mp4";
                //String strUrl = "http://play.g3proxy.lecloud.com/vod/v2/MjQ5LzM3LzIwL2xldHYtdXRzLzE0L3Zlcl8wMF8yMi0xMTA3NjQxMzkwLWF2Yy00MTk4MTAtYWFjLTQ4MDAwLTUyNjExMC0zMTU1NTY1Mi00ZmJjYzFkNzA1NWMyNDc4MDc5OTYxODg1N2RjNzEwMi0xNDk4NTU3OTYxNzQ4Lm1wNA==?b=479&mmsid=65565355&tm=1499247143&key=98c7e781f1145aba07cb0d6ec06f6c12&platid=3&splatid=345&playid=0&tss=no&vtype=13&cvid=2026135183914&payff=0&pip=08cc52f8b09acd3eff8bf31688ddeced&format=0&sign=mb&dname=mobile&expect=1&tag=mobile&xformat=super";
                //String strUrl = "rtmp://live.hkstv.hk.lxdns.com/live/hks";
                String strUrl = "http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8";
                //String strUrl = "http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8";

                NativePlayer.playVideo(strUrl, mSurfaceHolder.getSurface());
            }
        }).start();
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        new Thread(new Runnable() {
            @Override
            public void run() {

            }
        }).start();
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }
}
