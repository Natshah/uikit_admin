<?php

/**
 * @file
 * Set up variables to be placed within the template (.html.twig) files.
 *
 * @see process.inc
 */

use Drupal\Core\Render\Markup;
use Drupal\Core\Template\Attribute;
use Drupal\uikit\UIkit;

/**
 * Implements template_preprocess_page().
 */
function uikit_admin_preprocess_page(&$variables) {
  $theme_key = \Drupal::theme()->getActiveTheme()->getName();
  $sticky_nav = UIkit::getThemeSetting('sticky_navbar', $theme_key);

  $variables['header_attributes']->addClass('uk-margin-small-bottom');

  if ($sticky_nav) {
    $variables['#attached']['drupalSettings']['uikitAdmin']['stickyNavbar'] = TRUE;
  }
  else {
    $variables['#attached']['drupalSettings']['uikitAdmin']['stickyNavbar'] = FALSE;
  }

  $variables['navbar_attributes'] = new Attribute();
  $variables['navbar_attributes']->setAttribute('id', 'page--navbar');
  $variables['navbar_attributes']->addClass('uk-navbar');

  $variables['page_attributes'] = new Attribute();
  $variables['page_attributes']->setAttribute('id', 'page');
  $variables['page_attributes']->addClass('uk-container');
  $variables['page_attributes']->addClass('uk-container-expand');

  $variables['content_attributes'] = new Attribute();
  $variables['content_attributes']->setAttribute('id', 'page--content');
  $variables['content_attributes']->addClass('uk-width-1-1');
  $variables['content_attributes']->addClass('uk-margin-remove-top');
}

/**
 * Implements template_preprocess_region().
 */
function uikit_admin_preprocess_region(&$variables) {
  switch ($variables['region']) {
    case 'breadcrumb':
    case 'content':
    case 'help':
      $variables['attributes']['class'][] = 'uk-card';
      $variables['attributes']['class'][] = 'uk-card-default';
      $variables['attributes']['class'][] = 'uk-card-small';
      $variables['attributes']['class'][] = 'uk-card-body';
      $variables['attributes']['class'][] = 'uk-margin-small-bottom';
      break;

    case 'status_messages':
      $messages = drupal_get_messages(NULL, FALSE);

      if (empty($messages)) {
        $variables['content'] = [];
      }
      break;
  }
}

/**
 * Implements template_preprocess_block().
 */
function uikit_admin_preprocess_block(&$variables) {
  $block = \Drupal::entityTypeManager()->getStorage('block')->load($variables['elements']['#id']);

  if ($block->getRegion() == 'offcanvas') {
    $variables['content']['#theme'] = $variables['content']['#theme'] . '__offcanvas';
  }
}

/**
 * Implements template_preprocess_container().
 */
function uikit_admin_preprocess_container(&$variables) {
  $variables['form_row'] = TRUE;
  $variables['form_margin'] = TRUE;

  if (isset($variables['element']['#view_id'])) {
    $variables['form_row'] = FALSE;
    $variables['form_margin'] = FALSE;
  }

  $attributes = is_array($variables['attributes']) ? $variables['attributes'] : [];
  $classes = isset($attributes['class']) && is_array($attributes['class']) ? $attributes['class'] : [];

  if (in_array('toolbar-menu-administration', $classes)) {
    $variables['form_margin'] = FALSE;
  }
}

/**
 * Implements template_preprocess_input().
 */
function uikit_admin_preprocess_input(&$variables) {
  if ($variables['element']['#type'] == 'submit' || $variables['element']['#type'] == 'button') {
    $variables['attributes']['class'][] = 'uk-button-small';
  }
}

/**
 * Implements template_preprocess_links() for links--dropbutton.html.twig.
 */
function uikit_admin_preprocess_links__dropbutton(&$variables) {
  $links = $variables['links'];

  if (isset($variables['dropbutton'])) {
    $options = $variables['dropbutton']['link']['#options'];
    $classes = isset($options['attributes']['class']) ? $options['attributes']['class'] : [];

    if ($classes && ($key = array_search('uk-button', $classes)) !== false) {
      unset($variables['dropbutton']['link']['#options']['attributes']['class'][$key]);
    }

    if ($classes && ($key = array_search('uk-button-default', $classes)) !== false) {
      unset($variables['dropbutton']['link']['#options']['attributes']['class'][$key]);
    }

    array_unshift($links, $variables['dropbutton']);
  }

  $variables['links'] = $links;
}

/**
 * Implements template_preprocess_menu_local_tasks().
 */
function uikit_admin_preprocess_menu_local_tasks(&$variables) {
  /** @var \Drupal\Core\Menu\LocalTaskManagerInterface $manager */
  $manager = \Drupal::service('plugin.manager.menu.local_task');
  $tasks = $manager->getLocalTasksForRoute(\Drupal::routeMatch()->getRouteName());

  $variables['primary_attributes'] = new Attribute();
  $variables['primary_attributes']->addClass('uk-navbar-nav');

  $variables['secondary_attributes'] = new Attribute();
  $variables['secondary_attributes']->addClass('uk-nav');
  $variables['secondary_attributes']->addClass('uk-nav-default');

  if (count($tasks) > 1) {
    $variables['secondary_tasks'] = TRUE;
  }
  else {
    $variables['secondary_tasks'] = FALSE;
  }
}

/**
 * Implements template_preprocess_page_title().
 */
function uikit_admin_preprocess_page_title(&$variables) {
  $variables['title_attributes']['id'] = 'page-title';
  $variables['title_attributes']['class'][] = 'uk-navbar-item';
}

/**
 * Implements hook_preprocess_HOOK() for system_modules_details.html.twig.
 */
function uikit_admin_preprocess_system_modules_details(&$variables) {
  foreach ($variables['modules'] as $module_key => $module) {
    if (isset($variables['modules'][$module_key]['links'])) {
      foreach ($variables['modules'][$module_key]['links'] as $link_key => $link) {
        $icon = FALSE;

        switch ($link_key) {
          case 'help':
            $icon = Markup::create('<span class="uk-margin-small-right uk-icon" uk-icon="icon: question"></span> Help');
            break;

          case 'permissions':
            $icon = Markup::create('<span class="uk-margin-small-right uk-icon" uk-icon="icon: lock"></span> Permissions');
            break;

          case 'configure':
            $icon = Markup::create('<span class="uk-margin-small-right uk-icon" uk-icon="icon: cog"></span> Configure');
            break;
        }

        if ($icon) {
          $variables['modules'][$module_key]['links'][$link_key]['#title'] = t('@icon', ['@icon' => $icon]);
        }
      }
    }
  }
}
