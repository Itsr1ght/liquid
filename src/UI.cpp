/*
**  Includes
*/

#include "UI.hpp"

/*
**  Globals
*/


int sound_var = 128;
int sound_tmp;
bool vol_change = false;
bool stay = false;
static bool first = true;
bool req_pause = false;
bool req_seek = false;
bool req_mute = false;
bool req_audio_track_change = false;
bool req_sub_track_change = false;
bool draw_ui = true;
bool req_seek_progress = false;
double ui_incr;
double cur_tim;
int cur_sec;
int cur_min;
int cur_hur;
float progress_var;

/*
**  Functions
*/

void init_imgui(SDL_Window* window, SDL_Renderer* renderer)
{

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.IniFilename = NULL;
    // Setup Dear ImGui style
    ImGui::StyleColorsLight();
    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // context is the SDL_GLContext
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);
}

void update_imgui(SDL_Renderer* renderer, int width, int height)
{ 
    if(draw_ui){
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        //imgui window flags
        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoTitleBar;
        flags |= !ImGuiWindowFlags_MenuBar;
        flags |= ImGuiWindowFlags_NoResize;
        flags |= ImGuiWindowFlags_NoMove;

        //imgui child window flags
        ImGuiWindowFlags child_window_flags = 0;
        child_window_flags |= ImGuiWindowFlags_NoTitleBar;
        child_window_flags |= !ImGuiWindowFlags_MenuBar;
        child_window_flags |= ImGuiWindowFlags_NoResize;
        child_window_flags |= ImGuiWindowFlags_NoMove;


        //imgui style flags
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 5;
        style.ChildRounding = 12;
        style.TabRounding = 12;
        style.FrameRounding = 12;
        style.GrabRounding = 12;

        style.Colors[ImGuiCol_Text]                  = ImVec4(0.73f, 0.73f, 0.73f, 1.00f);
        style.Colors[ImGuiCol_TextDisabled]          = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        style.Colors[ImGuiCol_WindowBg]              = ImVec4(0.26f, 0.26f, 0.26f, 0.95f);
        style.Colors[ImGuiCol_PopupBg]               = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        style.Colors[ImGuiCol_Border]                = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        style.Colors[ImGuiCol_BorderShadow]          = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        style.Colors[ImGuiCol_FrameBg]               = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
        style.Colors[ImGuiCol_FrameBgHovered]        = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
        style.Colors[ImGuiCol_FrameBgActive]         = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
        style.Colors[ImGuiCol_TitleBg]               = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_TitleBgCollapsed]      = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_TitleBgActive]         = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_MenuBarBg]             = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarBg]           = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrab]         = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabHovered]  = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_ScrollbarGrabActive]   = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_CheckMark]             = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
        style.Colors[ImGuiCol_SliderGrab]            = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
        style.Colors[ImGuiCol_SliderGrabActive]      = ImVec4(0.74f, 0.74f, 0.74f, 1.00f);
        style.Colors[ImGuiCol_Button]                = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_ButtonHovered]         = ImVec4(0.43f, 0.43f, 0.43f, 1.00f);
        style.Colors[ImGuiCol_ButtonActive]          = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
        style.Colors[ImGuiCol_Header]                = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_HeaderHovered]         = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_HeaderActive]          = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_ResizeGrip]            = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
        style.Colors[ImGuiCol_ResizeGripHovered]     = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_ResizeGripActive]      = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
        style.Colors[ImGuiCol_PlotLines]             = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
        style.Colors[ImGuiCol_PlotLinesHovered]      = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogram]         = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_PlotHistogramHovered]  = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
        style.Colors[ImGuiCol_TextSelectedBg]        = ImVec4(0.32f, 0.52f, 0.65f, 1.00f);

        ImVec2 win_pos;
        ImVec2 main_win_pos;
        ImVec2 win_size;
        ImVec2 window_size;
        //render definition Here
        ImGui::Begin("Window",(bool *)true,flags);
        if (first)
        {
            window_size = {645, 61};
            ImGui::SetWindowSize(window_size);
        }
        win_size = ImGui::GetWindowSize();
        main_win_pos = {(float)(width/2) - (window_size.x/2), (float)height - 60};
        ImGui::SetWindowPos(main_win_pos);
        win_pos = ImGui::GetWindowPos();
        win_pos.y -= 110;
        ImGui::NewLine();
        // Fixme: Bad code
        ImGui::SameLine((ImGui::GetWindowWidth()*0.5) / 100);
        ImGui::LabelText("",current_time.c_str());
        ImGui::SameLine((ImGui::GetWindowWidth()*10) / 100);
        ImGui::PushItemWidth((ImGui::GetWindowWidth()*80) / 100);
        if(ImGui::SliderFloat("## ",&progress_var, 0.0f, 100.0f,"",ImGuiSliderFlags_AlwaysClamp | ImGuiSliderFlags_NoInput))
        {
            if(ImGui::IsMouseClicked(0))
            {
                std::cout<<"Requesting seek to: "<<progress_var<<std::endl;
                req_seek_progress = true;
            }
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*90) / 100);
        ImGui::LabelText("",max_video_duration.c_str());
        ImGui::NewLine();
        ImGui::SameLine((ImGui::GetWindowWidth()*10) / 100);
        if(ImGui::Button("M",{(win_size.x*4) / 100, 20}))
        {
            req_mute = true;
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*15) / 100);
        ImGui::PushItemWidth((ImGui::GetWindowWidth()*20) / 100);
        if(ImGui::SliderInt("  ",&sound_var, 0, 128) || ImGui::IsItemHovered()){
            if(ImGui::GetIO().MouseWheel){
                if((0 <= sound_var) && (sound_var <= 128)){
                    sound_tmp = sound_var + ImGui::GetIO().MouseWheel;
                    if((sound_tmp < 0) || (sound_tmp > 128)){
                        // Do nothing, already at the limits
                    }
                    else{
                        sound_var = sound_tmp;
                    }
                }
            }
            vol_change = true;
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*36) / 100);
        if(ImGui::Button("<<",{(win_size.x*5) /100, 20}))
        {
            ui_incr = -60.0;
            req_seek = true;
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*42) / 100);
        if(ImGui::Button("<",{(win_size.x*4) / 100, 20}))
        {
            ui_incr = -10.0;
            req_seek = true;
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*47.5) / 100);
        if(ImGui::Button("P",{(win_size.x*4) / 100, 20}))
        {
            req_pause = !req_pause;
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*53) / 100);
        if(ImGui::Button(">",{(win_size.x*4) / 100, 20}))
        {
            ui_incr = 10.0;
            req_seek = true;
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*58) / 100);
        if(ImGui::Button(">>",{(win_size.x*5) /100, 20}))
        {
            ui_incr = 60.0;
            req_seek = true;
        }

        ImGui::SameLine((ImGui::GetWindowWidth()*81) / 100);
        if(ImGui::Button("A",{(win_size.x*4) / 100, 20}))
        {

        }

        ImGui::SameLine((ImGui::GetWindowWidth()*86) / 100);
        if(ImGui::Button("S",{(win_size.x*4) / 100, 20}))
        {

        }

        ImGui::End();
        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    }
}

void imgui_event_handler(SDL_Event& event){
    ImGui_ImplSDL2_ProcessEvent(&event);
}

void destroy_imgui_data()
{
    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

bool want_capture_mouse()
{
    return ImGui::GetIO().WantCaptureMouse;
}

bool want_capture_keyboard()
{
    return ImGui::GetIO().WantCaptureKeyboard;
}

void change_imgui_win_size()
{
    first = true;
}

void end_win_size_change()
{
    first = false;
}
