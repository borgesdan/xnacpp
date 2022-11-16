#ifndef _GRAPHICSDEVICEMANAGER_HPP_
#define _GRAPHICSDEVICEMANAGER_HPP_

#include <cstdint>
#include <memory>
#include "Game.hpp"
#include "IGraphicsDeviceManager.hpp"
#include "GraphicsDeviceInformation.hpp"
#include "Graphics/SurfaceFormat.hpp"
#include "Graphics/GraphicsDevice.hpp"
#include "Graphics/IGraphicsDeviceService.hpp"
#include "Graphics/GraphicsProfile.hpp"
#include "Graphics/States/DepthFormat.hpp"

namespace Xna {

	using std::shared_ptr;
	using Graphics::IGraphicsDeviceService;
	using Graphics::GraphicsDevice;
	using Graphics::SurfaceFormat;
	using Graphics::DepthFormat;
	using Graphics::GraphicsProfile;
	using Graphics::PresentationParameters;

	class GraphicsDeviceManager : IGraphicsDeviceManager, IGraphicsDeviceService {
	private:
		shared_ptr<Game> _game;
		bool _initialized{ false };
		int32_t _preferredBackBufferHeight{ 0 };
		int32_t _preferredBackBufferWidth{ 0 };
		bool _preferMultiSampling{ false };
		bool _synchronizedWithVerticalRetrace{ true };
		bool _drawBegun{ false };
		bool _hardwareModeSwitch{ true };
		bool _preferHalfPixelOffset{ false };
		bool _wantFullScreen{ false };
		bool _shouldApplyChanges{ false };
		SurfaceFormat _preferredBackBufferFormat;
		DepthFormat _preferredDepthStencilFormat;
		GraphicsProfile _graphicsProfile;
		shared_ptr<GraphicsDevice> _graphicsDevice;

		GraphicsDeviceInformation DoPreparingDeviceSettings();

		void PlatformApplyChanges();
		void PlatformPreparePresentationParameters(PresentationParameters const& presentationParameters);
		void PreparePresentationParameters(PresentationParameters const& presentationParameters);

		void DisposeGraphicsDevice();
		void PlatformInitialize(Graphics::PresentationParameters const& presentationParameters);
		void Initialize(GraphicsDeviceInformation gdi);

	public:
		static constexpr int32_t DefaultBackBufferWidth = 800;
		static constexpr int32_t DefaultBackBufferHeight = 480;

		GraphicsDeviceManager(shared_ptr<Game> const& game);
		~GraphicsDeviceManager();

		void PlatformConstruct();
		void CreateDevice(GraphicsDeviceInformation const& gdi);

		virtual bool BeginDraw();
		virtual void CreateDevice();
		virtual void EndDraw();
		virtual Graphics::GraphicsDevice GetGraphicsDevice();

		void ApplyChanges();
		void ToggleFullScreen();

		Graphics::GraphicsProfile GraphicsProfile();
		void GraphicsProfile(Graphics::GraphicsProfile value);

		Graphics::GraphicsDevice GraphicsDevice();
		void GraphicsDevice(Graphics::GraphicsDevice value);
		bool IsFullScreen();
		void IsFullScreen(bool value);
		bool HardwareModeSwitch();
		void HardwareModeSwitch(bool value);
		bool PreferHalfPixelOffset();
		void PreferHalfPixelOffset(bool value);
		bool PreferMultiSampling();
		void PreferMultiSampling(bool value);
		Graphics::SurfaceFormat PreferredBackBufferFormat();
		void PreferredBackBufferFormat(Graphics::SurfaceFormat value);
		int32_t PreferredBackBufferHeight();
		void PreferredBackBufferHeight(int32_t value);
		int32_t PreferredBackBufferWidth();
		void PreferredBackBufferWidth(int32_t value);
		Graphics::DepthFormat PreferredDepthStencilFormat();
		void PreferredDepthStencilFormat(Graphics::DepthFormat value);
		bool SynchronizeWithVerticalRetrace();
		void SynchronizeWithVerticalRetrace(bool value);

		//TODO: adicionar eventos
		//public event EventHandler<EventArgs> DeviceCreated;		
		//public event EventHandler<EventArgs> DeviceDisposing;
		//public event EventHandler<EventArgs> DeviceResetting;		
		//public event EventHandler<EventArgs> DeviceReset;

		//void OnDeviceCreated(EventArgs e);
		//void OnDeviceDisposing(EventArgs e);
		//void OnDeviceResetting(EventArgs e);
		//void OnDeviceReset(EventArgs e);

		//event EventHandler<PreparingDeviceSettingsEventArgs> PreparingDeviceSettings;
		//void OnPresentationChanged(object sender, PresentationEventArgs args);
	};
}

#endif