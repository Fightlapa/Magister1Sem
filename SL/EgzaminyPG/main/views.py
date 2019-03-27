from django.shortcuts import render, redirect, get_object_or_404
from django.http import HttpRequest
from django.contrib import messages
from django.contrib.auth import models
from django.contrib.auth.mixins import LoginRequiredMixin, UserPassesTestMixin
from .models import ExamTemplate, Exam, PGUser
from .forms import PGUserRegisterForm, ExamForm
from django.contrib.auth.models import Permission
from django.contrib.auth.models import Group

# default template for these classes are: app/modelname_method.html
from django.views.generic import ListView, DetailView, CreateView, UpdateView, DeleteView
from django.utils import timezone

# Use it in templates to chcek normal permissions
# {% if perms.main.view_examtemplates %}

# Create your views here.

def home(request):
    """Renders the home page."""
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/index.html',
        {
            'title':'Strona główna'
        }
    )

def register(request):
    """Renders the home page."""
    if request.method == 'POST':
        form = PGUserRegisterForm(request.POST)
        if form.is_valid():
            form.save()
            username = form.cleaned_data.get('username')
            messages.success(request, f'Stworzono użytkownika o nazwie {username}!')
            return redirect('main-login')
    else:
        form = PGUserRegisterForm()
    assert isinstance(request, HttpRequest)
    return render(
        request,
        'app/register.html',
        {'form': form}
    )

class exam_templates_list_view(LoginRequiredMixin, UserPassesTestMixin, ListView):
    model = ExamTemplate
    context_object_name = 'templates' # name of collection seen in template
    # Use it in case of skipping get_queryset
    #ordering = ['-date_modified']
    paginate_by = 3

    def get_queryset(self):
        # Not used until you use parameters, it means that there is variable in url like /user/{int}
        # user = get_object_or_404(PGUser, username=self.kwargs.get('paramname'))
        return ExamTemplate.objects.filter(teacher=self.request.user).order_by('-date_modified')

    # If authorized
    def test_func(self):
        # if self.request.user.has_perm('main.view_exam template'):
        if self.request.user in PGUser.objects.filter(groups__name='teachers'):
            return True
        return False

class exam_template_detail_view(LoginRequiredMixin, UserPassesTestMixin, DetailView):
    model = ExamTemplate

    def get_context_data(self, **kwargs):
        context = super(exam_template_detail_view, self).get_context_data(**kwargs) # get the default context data
        context['exams'] = Exam.objects.filter(exam_template=self.kwargs['pk']) # add extra field to the context
        return context

    # If authorized
    def test_func(self):
        # if self.request.user.has_perm('main.view_exam template'):
        if self.request.user in PGUser.objects.filter(groups__name='teachers'):
            return True
        return False

class exam_template_create_view(LoginRequiredMixin, UserPassesTestMixin, CreateView):
    model = ExamTemplate
    fields = ['name', 'image']

    def form_valid(self, form):
        form.instance.teacher = self.request.user
        return super().form_valid(form)

    # If authorized
    def test_func(self):
        # if self.request.user.has_perm('main.add_exam template'):
        if self.request.user in PGUser.objects.filter(groups__name='teachers'):
            return True
        return False

class exam_template_update_view(LoginRequiredMixin, UserPassesTestMixin, UpdateView):
    model = ExamTemplate
    fields = ['name', 'image']

    def form_valid(self, form):
        form.instance.teacher = self.request.user
        form.instance.date_modified = timezone.now
        return super().form_valid(form)

    # If authorized
    def test_func(self):
        exam_template = self.get_object()
        # if self.request.user.has_perm('main.change_exam template') and self.request.user == exam_template.teacher:
        if self.request.user in PGUser.objects.filter(groups__name='teachers') and self.request.user == exam_template.teacher:
            return True
        return False

class exam_template_delete_view(LoginRequiredMixin, UserPassesTestMixin, DeleteView):
    model = ExamTemplate
    success_url = '/'

    # If authorized
    def test_func(self):
        exam_template = self.get_object()
        # if self.request.user.has_perm('main.delete_exam template') and self.request.user == exam_template.teacher:
        if self.request.user in PGUser.objects.filter(groups__name='teachers') and self.request.user == exam_template.teacher:
            return True
        return False

class exam_list_view(LoginRequiredMixin, UserPassesTestMixin, ListView):
    model = Exam
    context_object_name = 'exams' # name of collection seen in template
    # Use it in case of skipping get_queryset
    #ordering = ['-date_modified']
    paginate_by = 3

    def get_queryset(self):
        # Not used until you use parameters, it means that there is variable in url like /user/{int}
        # user = get_object_or_404(PGUser, username=self.kwargs.get('paramname'))
        return Exam.objects.filter(student=self.request.user).order_by('-date_modified')

    # If authorized
    def test_func(self):
        # if self.request.user.has_perm('main.view_exam'):
        if self.request.user in PGUser.objects.filter(groups__name='students'):
            return True
        return False


class exam_create_view(LoginRequiredMixin, UserPassesTestMixin, CreateView):
    model = Exam
    form_class = ExamForm

    def form_valid(self, form):
        form.instance.teacher = self.request.user
        exam_template = self.get_queryset()
        form.instance.exam_template = exam_template
        return super().form_valid(form)

    def get_queryset(self):
        # Not used until you use parameters, it means that there is variable in url like /user/{int}
        return get_object_or_404(ExamTemplate, id=self.kwargs.get('exam_template'))

    # If authorized
    def test_func(self):
        # if self.request.user.has_perm('main.create_exam'):
        if self.request.user in PGUser.objects.filter(groups__name='teachers'):
            return True
        return False

class exam_detail_view(LoginRequiredMixin, UserPassesTestMixin, DetailView):
    model = Exam

    # If authorized
    def test_func(self):
        exam = self.get_object()
        # if self.request.user.has_perm('main.view_exam') and self.request.user == exam.exam_template.teacher or self.request.user == exam.student:
        if self.request.user.groups.filter(name__in=['students', 'teachers']).exists() and (self.request.user == exam.exam_template.teacher or self.request.user == exam.student):
            return True
        return False

class exam_update_view(LoginRequiredMixin, UserPassesTestMixin, UpdateView):
    model = Exam
    fields = ['image']

    def form_valid(self, form):
        form.instance.date_modified = timezone.now
        return super().form_valid(form)

    # If authorized
    def test_func(self):
        exam = self.get_object()
        # if self.request.user.has_perm('main.change_exam') and self.request.user == exam.exam_template.teacher or self.request.user == exam.student:
        if self.request.user in PGUser.objects.filter(groups__name='teachers') and self.request.user == exam.exam_template.teacher or self.request.user == exam.student:
            return True
        return False

class exam_delete_view(LoginRequiredMixin, UserPassesTestMixin, DeleteView):
    model = Exam
    success_url = '/'

    # If authorized
    def test_func(self):
        exam = self.get_object()
        # if self.request.user.has_perm('main.delete_exam') and self.request.user == exam.exam_template.teacher:
        if self.request.user in PGUser.objects.filter(groups__name='teachers') and self.request.user == exam.exam_template.teacher:
            return True
        return False
