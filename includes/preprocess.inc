<?php

/**
 * @file
 * Set up variables to be placed within the template (.html.twig) files.
 *
 * @see process.inc
 */

use Drupal\Core\Template\Attribute;

/**
 * Implements template_preprocess_page().
 */
function uikit_admin_preprocess_page(&$variables) {
  $variables['header_attributes']->addClass('uk-margin-small-bottom');

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
  if ($variables['element']['#type'] == 'submit') {
    $value = $variables['element']['#value'];
    $variables['attributes']['class'][] = 'uk-button';

    switch (TRUE) {
      case preg_match('/Apply.*/', $value):
      case preg_match('/Filter.*/', $value):
      case preg_match('/Generate.*/', $value):
      case preg_match('/Install.*/', $value):
      case preg_match('/Save.*/', $value):
        $variables['attributes']['class'][] = 'uk-button-primary';
        break;

      case preg_match('/Delete.*/', $value):
      case preg_match('/Remove.*/', $value):
        $variables['attributes']['class'][] = 'uk-button-danger';
        break;

      default:
        $variables['attributes']['class'][] = 'uk-button-default';
    }

    $variables['attributes']['class'][] = 'uk-button-small';
  }
}

/**
 * Implements template_preprocess_links() for links--dropbutton.html.twig.
 */
function uikit_admin_preprocess_links__dropbutton(&$variables) {
  $links = $variables['links'];
  $multiple = count($links) > 1 ? TRUE : FALSE;

  if ($multiple) {
    if (isset($variables['dropbutton']['link']) && $variables['dropbutton']['link']) {
      $variables['dropbutton']['link']['#options']['attributes']['class'] = ['uk-button'];
      $variables['dropbutton']['link']['#options']['attributes']['class'][] = 'uk-button-primary';
      $variables['dropbutton']['link']['#options']['attributes']['class'][] = 'uk-button-small';
    }
    else {
      $variables['dropbutton']['attributes']->addClass('uk-button');
      $variables['dropbutton']['attributes']->addClass('uk-button-primary');
      $variables['dropbutton']['attributes']->addClass('uk-button-small');
    }
  }
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
