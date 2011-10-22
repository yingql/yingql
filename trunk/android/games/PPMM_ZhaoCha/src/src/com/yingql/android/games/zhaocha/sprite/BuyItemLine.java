package com.yingql.android.games.zhaocha.sprite;

import com.mobclick.android.MobclickAgent;
import com.wiyun.engine.nodes.AtlasLabel;
import com.wiyun.engine.nodes.Button;
import com.wiyun.engine.nodes.Node;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.types.WYPoint;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.MainActivity;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.entity.UserInfo;
import com.yingql.android.games.zhaocha.scene.GameScene;
import com.yingql.android.games.zhaocha.util.GameUtil;
import com.yingql.android.games.zhaocha.util.db.DatabaseOperator;

public class BuyItemLine extends Node
{
	public static final int TYPE_FIND = 1;
	public static final int TYPE_CLOCK = 2;
	private int type;
	private int count;
	private int price;

	public BuyItemLine(int type, int itemId, int count, int price, boolean isCheapest)
	{
		this.type = type;
		this.count = count;
		this.price = price;

		int bgId = isCheapest ? R.drawable.buy_item_line_bg2 : R.drawable.buy_item_line_bg;
		Sprite bg = Sprite.make(bgId);
		bg.setAnchorPercent(0, 0f);
		this.addChild(bg, 1);
		bg.autoRelease();

		Sprite icon = Sprite.make(itemId);
		icon.setAnchorPercent(0, 0f);
		icon.setPosition(ResolutionIndependent.resolve(WYPoint.make(20, -2)));
		this.addChild(icon, 1);
		icon.autoRelease();

		Texture2D texture = Texture2D.makePNG(R.drawable.numbers);

		AtlasLabel lbCount = AtlasLabel.make(this.count + "", texture, GameSystem.WhiteCharMap);
		lbCount.setAnchorPercent(1, 0);
		lbCount.setPosition(ResolutionIndependent.resolve(WYPoint.make(100, 4)));
		this.addChild(lbCount, 1);
		lbCount.autoRelease();

		AtlasLabel lbPrice = AtlasLabel.make(":" + this.price, texture, GameSystem.WhiteCharMap);
		lbPrice.setAnchorPercent(1, 0);
		lbPrice.setPosition(ResolutionIndependent.resolve(WYPoint.make(180, 4)));
		this.addChild(lbPrice, 1);
		lbPrice.autoRelease();

		Button btnBuy = Button.make(R.drawable.btn_buy_normal, R.drawable.btn_buy_active, this, "buyItem");
		btnBuy.setAnchorPercent(0, 0);
		btnBuy.setPosition(ResolutionIndependent.resolve(WYPoint.make(195, 0)));
		this.addChild(btnBuy, 1);
		btnBuy.autoRelease();

		if (isCheapest)
		{
			Sprite chepIcon = Sprite.make(R.drawable.buy_icon);
			chepIcon.setAnchorPercent(0.5f, 0f);
			chepIcon.setPosition(ResolutionIndependent.resolve(WYPoint.make(0, -4)));
			this.addChild(chepIcon, 1);
			chepIcon.autoRelease();
		}
	}

	public void buyItem()
	{
		// 根据持有的金币数进行判断，如果够则增加对应的道具量，否则Toast提示金币不足
		UserInfo user = DatabaseOperator.getUserInfo();
		int coins = user.getCoins();
		if (coins >= this.getPrice())
		{
			user.setCoins(coins - this.getPrice());
			GameScene.getInstance().updateCoins(user.getCoins());
			if (this.type == TYPE_FIND)
			{
				user.setFindItemCount(user.getFindItemCount() + this.getCount());
				GameSystem.getGameInfo().setFindItemCount(user.getFindItemCount());
				GameScene.getInstance().getGameBGLayer().getBoard().setFindItemCount(user.getFindItemCount());
				MobclickAgent.onEvent(MainActivity.Instance, GameUtil.EVENT_BUY_FIND, "Count_" + this.getCount());
			}
			else if (this.type == TYPE_CLOCK)
			{
				user.setClockItemCount(user.getClockItemCount() + this.getCount());
				GameSystem.getGameInfo().setClockItemCount(user.getClockItemCount());
				GameScene.getInstance().getGameBGLayer().getBoard().setClockItemCount(user.getClockItemCount());
				MobclickAgent.onEvent(MainActivity.Instance, GameUtil.EVENT_BUY_CLOCK, "Count_" + this.getCount());
			}
			DatabaseOperator.saveUserInfo(user);
		}
		else
		{
			MainActivity.Instance.showTip("金币不足，点击下方广告即可获取金币.");
		}
	}

	public int getCount()
	{
		return count;
	}

	public int getPrice()
	{
		return price;
	}
}
