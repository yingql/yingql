package com.yingql.android.games.zhaocha.layer;

import com.wiyun.engine.nodes.Layer;
import com.wiyun.engine.nodes.Sprite;
import com.wiyun.engine.opengl.Texture2D;
import com.wiyun.engine.utils.ResolutionIndependent;
import com.yingql.android.games.zhaocha.R;
import com.yingql.android.games.zhaocha.core.GameSystem;
import com.yingql.android.games.zhaocha.entity.GameInfo;
import com.yingql.android.games.zhaocha.sprite.GameInfoBoard;

public class GameBGLayer extends Layer
{
	private GameInfoBoard board;

	public GameBGLayer()
	{
		Sprite bg = Sprite.make(Texture2D.makeJPG(R.drawable.background));
		this.addChild(bg, 1);
		bg.setPosition(GameSystem.Screen_Width / 2, GameSystem.Screen_Height / 2);
		bg.setScale(GameSystem.Screen_Width / bg.getWidth(), GameSystem.Screen_Height / bg.getHeight());
		bg.autoRelease();

		board = new GameInfoBoard();
		board.setAnchorPercent(0, 1);
		board.setPosition(ResolutionIndependent.resolveDp(400), GameSystem.Screen_Height);
		this.addChild(board, 1);
		board.autoRelease();
	}

	public GameInfoBoard getBoard()
	{
		return board;
	}

	public void init(GameInfo gameInfo)
	{
		board.init(gameInfo);
	}
}
