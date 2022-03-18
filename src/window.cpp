#include <map>
#include <glad/glad.h>
#include <quickjs-libc.h>



#include "core.h"
#include "common.h"

#include "config.h"

static int id = 0;
static std::map<int,seeker::Window*> windows;

static void window_thread(void * arg);
static void update_window(seeker::Window * window);
static void draw_window(seeker::Window * window);

int seeker::new_window(const std::string & args)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    auto window = new Window();

    window->id = ++id;
    window->width = 800;
    window->height = 600;
    window->title = "";
    window->args = args;
    window->loop = (uv_loop_t*) malloc(sizeof(uv_loop_t));
    window->real = glfwCreateWindow(window->width, window->height, window->title.c_str(), nullptr, nullptr);
    window->js = new_runtime();
    
    uv_loop_init(window->loop);
    glfwSetWindowUserPointer(window->real,window);

    windows[window->id] = window;

    return window->id;
}

void seeker::start_window(int id)
{
    auto it = windows.find(id);
    if(it == windows.end())
    {
        return;
    }

    auto window = it->second;

    auto func = [](GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);

        Window * self = (Window * )glfwGetWindowUserPointer(window);

        self->width = width;
        self->height = height;
    };

    glfwSetFramebufferSizeCallback(window->real,func);

    uv_thread_t thread;

    uv_thread_create(&thread, window_thread,window);
}

void seeker::stop_window(int window)
{
}

void window_thread(void * arg)
{
    auto self = (seeker::Window * )arg;

    glfwMakeContextCurrent(self->real);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to create the GLFW window\n");
        return;
    }

    glViewport(0, 0, self->width, self->height);

	auto Interface = GrGLMakeNativeInterface();
	self->sContext = GrDirectContext::MakeGL(Interface).release();

	GrGLFramebufferInfo framebufferInfo;
	framebufferInfo.fFBOID = 0; // assume default framebuffer
	// We are always using OpenGL and we use RGBA8 internal format for both RGBA and BGRA configs in OpenGL.
	//(replace line below with this one to enable correct color spaces) framebufferInfo.fFormat = GL_SRGB8_ALPHA8;
	framebufferInfo.fFormat = GL_RGBA8;

	SkColorType colorType = kRGBA_8888_SkColorType;
	GrBackendRenderTarget backendRenderTarget(self->width, self->height,
		0, // sample count
		0, // stencil bits
		framebufferInfo);

	//(replace line below with this one to enable correct color spaces) sSurface = SkSurface::MakeFromBackendRenderTarget(sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, SkColorSpace::MakeSRGB(), nullptr).release();
	self->sSurface = SkSurface::MakeFromBackendRenderTarget(self->sContext, backendRenderTarget, kBottomLeft_GrSurfaceOrigin, colorType, nullptr, nullptr).release();
	if (self->sSurface == nullptr) abort();

    auto on_timer = [](uv_timer_t* handle)
    {
        auto window = (seeker::Window * )handle->data;
        
        update_window(window);
    };

    seeker::enter_runtime(self->js,self->args);

    uv_timer_t timer_req;

    uv_timer_init(self->loop, &timer_req);

    timer_req.data = self;

    uv_timer_start(&timer_req, on_timer, 0, 1000 / 60);

    uv_run(self->loop, UV_RUN_DEFAULT);
}

void update_window(seeker::Window * window)
{
    if (!glfwWindowShouldClose(window->real))
    {
        if (glfwGetKey(window->real, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window->real, true);

        draw_window(window);


      
    }
}

void draw_window(seeker::Window * window)
{
        SkCanvas* canvas = window->sSurface->getCanvas();

        glClearColor(1.00f, 0.49f, 0.04f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);

        SkPaint paint;
		paint.setColor(SK_ColorWHITE);
		canvas->drawPaint(paint);
		paint.setColor(SK_ColorYELLOW);
		canvas->drawRect({100, 200, 300, 500}, paint);
		window->sContext->flush();

        glfwSwapBuffers(window->real);  
}
