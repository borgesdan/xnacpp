#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <memory>
#include <map>
#include <string>
#include "CSharp/TimeSpan.hpp"

namespace Xna {

	class GameWindow;
	class IGraphicsDeviceManager;
	class GraphicsDeviceManager;
	class IGraphicsDeviceService;
	class GraphicsDevice;
	class GameTime;

	class Game {		
	private:
		//GameComponentCollection _components;
		//GameServiceContainer _services;
		//ContentManager _content;
		std::map<std::string, std::string> launchParameters;
		std::shared_ptr<IGraphicsDeviceManager> _graphicsDeviceManager;
		std::shared_ptr<IGraphicsDeviceService> _graphicsDeviceService;
		bool _initialized{ false };
		bool _isFixedTimeStep{ true };
		bool _shouldExit{ false };
		bool _suppressDraw{ false };
		CSharp::TimeSpan _targetElapsedTime{ CSharp::TimeSpan::FromTicks(166667) };
		CSharp::TimeSpan _inactiveSleepTime{ CSharp::TimeSpan::FromSeconds(0.02) };
		CSharp::TimeSpan _maxElapsedTime{ CSharp::TimeSpan::FromMilliseconds(500) };

		static std::shared_ptr<Game> _instance;

		void PlatformConstruct();
		void InitializeExistingComponents();
		void CategorizeComponents();
		void DecategorizeComponents();
		//void CategorizeComponent(IGameComponent component)
		//void DecategorizeComponent(IGameComponent component)

		//static readonly Action<IDrawable, GameTime> DrawAction =(drawable, gameTime) = > drawable.Draw(gameTime)
		//void Components_ComponentAdded(object sender, GameComponentCollectionEventArgs e)
		//void Components_ComponentRemoved(object sender, GameComponentCollectionEventArgs e)
		//void Platform_AsyncRunLoopEnded(object sender, EventArgs e)

	protected:
		virtual bool BeginDraw();
		virtual void EndDraw();
		virtual void BeginRun();
		virtual void EndRun();
		virtual void LoadContent();
		virtual void UnloadContent();
		virtual void Initialize();
		virtual void Draw(GameTime const& gameTime);
		virtual void Update(GameTime const& gameTime);
		//virtual void OnExiting(object sender, EventArgs args);
		//virtual void OnActivated(object sender, EventArgs args);
		//virtual void OnDeactivated (object sender, EventArgs args);

	public:
		Game();
		~Game();

		static std::shared_ptr<Game> Instance();

		CSharp::TimeSpan InactiveSleepTime() const;
		void InactiveSleepTime(CSharp::TimeSpan const& value);
		CSharp::TimeSpan MaxElapsedTime() const;
		void MaxElapsedTime(CSharp::TimeSpan const& value);
		bool IsActive() const;
		bool IsMouseVisible() const;
		void IsMouseVisible(bool value);
		CSharp::TimeSpan TargetElapsedTime() const;
		void TargetElapsedTime(CSharp::TimeSpan const& value);
		bool IsFixedTimeStep() const;
		void IsFixedTimeStep(bool value);
		//GameServiceContainer Services() const;
		//ContentManager Content() const;
		//void Content(ContentManager value) const;
		std::shared_ptr<GraphicsDevice> GraphicsDevice();
		std::shared_ptr<GameWindow> Window();
		bool Initialized() const;
		void Exit();
		void ResetElapsedTime();
		void SuppressDraw();
		void RunOneFrame();
		void Run();
		//void Run(GameRunBehavior runBehavior);
		void Tick();
		//void applyChanges(GraphicsDeviceManager const& manager);
		void DoUpdate(GameTime const& gameTime);
		void DoDraw(GameTime const& gameTime);
		void DoInitialize();
		void DoExiting();

		//public event EventHandler<EventArgs> Activated;
		//public event EventHandler<EventArgs> Deactivated;
		//public event EventHandler<EventArgs> Exiting;

		std::map<std::string, std::string> LaunchParameters() const;
		// GameComponentCollection Components { get; }
		std::shared_ptr<GraphicsDeviceManager> graphicsDeviceManager();
		void graphicsDeviceManager(std::shared_ptr<GraphicsDeviceManager> value);
	};
}

#endif