package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.nodes.AtlasLabel;
import com.wiyun.engine.nodes.Button;
import com.wiyun.engine.nodes.Layer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.util.db.DatabaseOperator;

public abstract class BuyItemLayer extends Layer
{
	private AtlasLabel lbCoins;

	public BuyItemLayer()
	{
		float cx = GameSystem.Screen_Width / 2, cy = GameSystem.Screen_Height / 2;
		float y = ResolutionIndependent.resolveDp(55);
		float sx = cx - ResolutionIndependent.resolveDp(150);

		Sprite mask = Sprite.make(R.drawable.mask);
		mask.setPosition(WYPoint.make(cx, cy));
		mask.setScale(GameSystem.Screen_Width / mask.getWidth(), GameSystem.Screen_Height / mask.getHeight());
		this.addChild(mask, 0);
		mask.autoRelease();

		Sprite bg = Sprite.make(R.drawable.buy_item_bg);
		bg.setDither(true);
		bg.setAnchorPercentY(0);
		bg.setPosition(WYPoint.make(cx, y));
		this.addChild(bg, 1);
		bg.autoRelease();

		Sprite title = Sprite.make(getTitleBgId());
		title.setAnchorPercent(0, 0);
		title.setPosition(WYPoint.make(sx, y + ResolutionIndependent.resolveDp(200)));
		this.addChild(title, 1);
		title.autoRelease();

		Sprite icon = Sprite.make(getItemIconId());
		icon.setAnchorPercent(0, 0);
		icon.setPosition(WYPoint.make(sx + ResolutionIndependent.resolveDp(10), y + ResolutionIndependent.resolveDp(198)));
		this.addChild(icon, 1);
		icon.autoRelease();

		Button btnClose = Button.make(R.drawable.btn_close_normal, 0, this, "close");
		btnClose.setAnchorPercent(0, 0);
		btnClose.setPosition(WYPoint.make(sx + ResolutionIndependent.resolveDp(260), y + ResolutionIndependent.resolveDp(202)));
		this.addChild(btnClose, 1);
		btnClose.autoRelease();

		Sprite coins = Sprite.make(R.drawable.coins);
		coins.setAnchorPercent(0, 0);
		coins.setPosition(WYPoint.make(sx + ResolutionIndependent.resolveDp(190), y + ResolutionIndependent.resolveDp(40)));
		this.addChild(coins, 1);
		coins.autoRelease();

		Texture2D texture = Texture2D.makePNG(R.drawable.numbers);

		lbCoins = AtlasLabel.make("" + DatabaseOperator.getUserInfo().getCoins(), texture, GameSystem.WhiteCharMap);
		lbCoins.setAnchorPercent(0, 0);
		lbCoins.setPosition(WYPoint.make(sx + ResolutionIndependent.resolveDp(220), y + ResolutionIndependent.resolveDp(44)));
		this.addChild(lbCoins, 1);
		lbCoins.autoRelease();

		initBuyItemLines(sx, y);
	}

	public void updateCoins(int coins)
	{
		lbCoins.setText(coins + "");
	}

	public abstract void close();

	public abstract void initBuyItemLines(float x, float y);

	public abstract int getTitleBgId();

	public abstract int getItemIconId();
}
