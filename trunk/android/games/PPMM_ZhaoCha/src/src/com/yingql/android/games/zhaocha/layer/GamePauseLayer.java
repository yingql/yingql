package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.nodes.Button;
import com.wiyun.engine.nodes.Layer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.scene.StartScene;
import com.yingql.android.games.zhaocha.util.ADHelper;
import com.yingql.android.games.zhaocha.util.GameUtil;

public class GamePauseLayer extends Layer
{
	public GamePauseLayer()
	{
		float cx = GameSystem.Screen_Width / 2, cy = GameSystem.Screen_Height / 2;

		Sprite mask = Sprite.make(R.drawable.mask);
		mask.setPosition(WYPoint.make(cx, cy));
		mask.setScale(GameSystem.Screen_Width / mask.getWidth(), GameSystem.Screen_Height / mask.getHeight());
		this.addChild(mask, 0);
		mask.autoRelease();

		Button btnResume = Button.make(R.drawable.btn_pause_resume_normal, R.drawable.btn_pause_resume_active, this, "resume");
		btnResume.setPosition(WYPoint.make(cx, cy + ResolutionIndependent.resolveDp(70)));
		this.addChild(btnResume, 1);
		btnResume.autoRelease();

		Button btnRetry = Button.make(R.drawable.btn_pause_retry_normal, R.drawable.btn_pause_retry_active, this, "retry");
		btnRetry.setPosition(WYPoint.make(cx, cy));
		this.addChild(btnRetry, 1);
		btnRetry.autoRelease();

		Button btnMenu = Button.make(R.drawable.btn_pause_menu_normal, R.drawable.btn_pause_menu_active, this, "menu");
		btnMenu.setPosition(WYPoint.make(cx, cy - ResolutionIndependent.resolveDp(70)));
		this.addChild(btnMenu, 1);
		btnMenu.autoRelease();
	}

	public void resume()
	{
		GameScene.getInstance().resumeGame();
	}

	public void retry()
	{
		GameSystem.retry();
	}

	public void menu()
	{
		ADHelper.hideAd();
		GameSystem.saveGameProgress();
		GameUtil.switchScene(StartScene.make());
	}
}
