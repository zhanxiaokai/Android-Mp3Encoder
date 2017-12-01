package com.phuket.tour.mp3encoder;

import com.phuket.tour.studio.Mp3Encoder;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {

	static {
		System.loadLibrary("audioencoder");
	}
	private Button mp3_encoder_btn;
	private final String TAG = "MainActivity";
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		mp3_encoder_btn = (Button) findViewById(R.id.mp3_encoder_btn);
		mp3_encoder_btn.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				Mp3Encoder encoder = new Mp3Encoder();
				String pcmPath = "/mnt/sdcard/a_songstudio/vocal.pcm";
				int audioChannels = 2;
				int bitRate = 128 * 1024;
				int sampleRate = 44100;
				String mp3Path = "/mnt/sdcard/a_songstudio/vocal.mp3";
				int ret = encoder.init(pcmPath, audioChannels, bitRate, sampleRate, mp3Path);
				if(ret >= 0) {
					encoder.encode();
					encoder.destroy();
					Log.i(TAG, "Encode Mp3 Success");
				} else {
					Log.i(TAG, "Encoder Initialized Failed...");
				}
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
