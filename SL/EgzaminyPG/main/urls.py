from django.urls import path, re_path
from . import views
from .views import exam_templates_list_view, exam_template_detail_view, exam_template_create_view, exam_template_update_view, exam_template_delete_view
from .views import exam_list_view, exam_detail_view, exam_create_view
urlpatterns = [
    path('', views.home, name = 'main-home'),
    path('register/', views.register, name = 'main-register'),
]

exam_templates_urls = [
    path('exam-templates/', exam_templates_list_view.as_view(), name ='main-exam-templates'),
    path('exam-templates/<int:pk>/', exam_template_detail_view.as_view(), name ='main-exam-template-detail'), # pk means primary key
    path('exam-templates/new/', exam_template_create_view.as_view(), name ='main-create-exam-template'),
    path('exam-templates/<int:pk>/update/', exam_template_update_view.as_view(), name ='main-update-exam-template'),
    path('exam-templates/<int:pk>/delete/', exam_template_delete_view.as_view(), name ='main-delete-exam-template'),
]

exam_urls = [
    path('exam/', exam_list_view.as_view(), name ='main-exam'),
    path('exam/new/<int:exam_template>/', exam_create_view.as_view(), name ='main-create-exam'),
    path('exam/<int:pk>/', exam_detail_view.as_view(), name ='main-exam-detail'), # pk means primary key
]

urlpatterns += exam_templates_urls
urlpatterns += exam_urls
