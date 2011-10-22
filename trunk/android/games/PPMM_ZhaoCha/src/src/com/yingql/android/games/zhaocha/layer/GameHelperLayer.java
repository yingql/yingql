package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.nodes.Button;
import com.wiyun.engine.nodes.Layer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.scene.StartScene;

public class GameHelperLayer extends Layer
{
	public GameHelperLayer()
	{
		float cx = GameSystem.Screen_Width / 2, cy = GameSystem.Screen_Height / 2;

		Sprite mask = Sprite.make(R.drawable.mask);
		mask.setPosition(WYPoint.make(cx, cy));
		mask.setScale(GameSystem.Screen_Width / mask.getWidth(), GameSystem.Screen_Height / mask.getHeight());
		this.addChild(mask, 0);
		mask.autoRelease();
		
		Sprite bg = Sprite.make(R.drawable.howtoplay);
		bg.setDither(true);
		bg.setPosition(WYPoint.make(cx, cy));
		this.addChild(bg, 1);
		bg.autoRelease();

		Button btnCancel = Button.make(R.drawable.cancel, 0, this, "close");
		btnCancel.setPosition(WYPoint.make(cx + ResolutionIndependent.resolveDp(118), cy + ResolutionIndependent.resolveDp(130)));
		this.addChild(btnCancel, 1);
		btnCancel.autoRelease();
	}

	public void close()
	{
		StartScene.getInstance().closeHelp();
	}
}
