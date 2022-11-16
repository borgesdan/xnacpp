#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <memory>
#include "GameWindow.hpp"
#include "IGraphicsDeviceManager.hpp""
#include "GraphicsDeviceManager.hpp"
#include "GameTime.hpp"
#include "Graphics/IGraphicsDeviceService.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "CSharp/TimeSpan.hpp"

using std::shared_ptr;
using CSharp::TimeSpan;
using Xna::Graphics::IGraphicsDeviceService;
using Xna::Graphics::GraphicsDevice;

namespace Xna {

	class Game {		
	private:
		//GameComponentCollection _components;
		//GameServiceContainer _services;
		//ContentManager _content;
		shared_ptr<IGraphicsDeviceManager> _graphicsDeviceManager;
		shared_ptr<IGraphicsDeviceService> _graphicsDeviceService;		
		bool _initialized{ false };
		bool _isFixedTimeStep{ true };
		bool _shouldExit{ false };
		bool _suppressDraw{ false };
		TimeSpan _targetElapsedTime{ TimeSpan::FromTicks(166667) };
		TimeSpan _inactiveSleepTime{ TimeSpan::FromSeconds(0.02) };
		TimeSpan _maxElapsedTime{ TimeSpan::FromMilliseconds(500) };

		static shared_ptr<Game> _instance;

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

		static shared_ptr<Game> Instance();

		TimeSpan InactiveSleepTime() const;
		void InactiveSleepTime(TimeSpan const& value);
		TimeSpan MaxElapsedTime() const;
		void MaxElapsedTime(TimeSpan const& value);
		bool IsActive() const;
		bool IsMouseVisible() const;
		void IsMouseVisible(bool value);
		TimeSpan TargetElapsedTime() const;
		void TargetElapsedTime(TimeSpan const& value);
		bool IsFixedTimeStep() const;
		void IsFixedTimeStep(bool value);
		//GameServiceContainer Services() const;
		//ContentManager Content() const;
		//void Content(ContentManager value) const;
		shared_ptr<GraphicsDevice> GraphicsDevice();
		shared_ptr<GameWindow> Window();
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

		// LaunchParameters LaunchParameters { get; private set; }
		// GameComponentCollection Components { get; }
		//GraphicsDeviceManager graphicsDeviceManager();
		void graphicsDeviceManager(shared_ptr<GraphicsDeviceManager> value);
	};
}

#endif