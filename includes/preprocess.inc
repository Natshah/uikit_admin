<?php

/**
 * @file
 * Set up variables to be placed within the template (.tpl.php) files.
 *
 * @see process.inc
 */

use Drupal\Core\Template\Attribute;
use Drupal\uikit_admin\UIkitAdmin;

/**
 * Implements template_preprocess_page().
 */
function uikit_admin_preprocess_page(&$variables) {
  // Set page.html.twig template attributes.
  $page_attributes = UIkitAdmin::getPageTemplateAttributes();
  $variables['header_attributes'] = $page_attributes['header_attributes'];
  $variables['pre_content_attributes'] = $page_attributes['pre_content_attributes'];
  $variables['breadcrumb_attributes'] = $page_attributes['breadcrumb_attributes'];
  $variables['highlighted_attributes'] = $page_attributes['highlighted_attributes'];
  $variables['help_attributes'] = $page_attributes['help_attributes'];
  $variables['content_wrapper_attributes'] = $page_attributes['content_wrapper_attributes'];
  $variables['content_attributes'] = $page_attributes['content_attributes'];
}

/**
 * Implements template_preprocess_input().
 */
function uikit_admin_preprocess_input(&$variables) {
  $type = $variables['element']['#type'];

  if ($type == 'submit') {
    $value = $variables['element']['#value']->getUntranslatedString();
    $variables['value'] = t('@value', ['@value' => $value]);
    $variables['attributes']['class'][] = 'uk-button';

    switch ($value) {
      case 'Save configuration':
        $variables['attributes']['class'][] = 'uk-button-primary';
        break;
    }
  }
}

/**
 * Implements template_preprocess_links() for dropbutton links.
 */
function uikit_admin_preprocess_links__dropbutton(&$variables) {
  if ($variables['dropbutton']['link']) {
    $variables['dropbutton']['link']['#options']['attributes']['class'][] = 'uk-button-primary';
  }
  elseif ($variables['dropbutton']['text_attributes']) {
    $variables['dropbutton']['text_attributes']['class'][] = 'uk-button-primary';
  }
}

/**
 * Implements template_preprocess_menu_local_tasks().
 */
function uikit_admin_preprocess_menu_local_tasks(&$variables) {
  // Set primary tasks attributes.
  $primary_attributes = new Attribute;
  $primary_attributes->setAttribute('id', 'tasks--primary');
  $primary_attributes->addClass('uk-tab');
  $variables['primary_attributes'] = $primary_attributes;

  // Set secondary tasks attributes.
  $secondary_attributes = new Attribute;
  $secondary_attributes->setAttribute('id', 'tasks-secondary');
  $secondary_attributes->addClass('uk-subnav');
  $secondary_attributes->addClass('uk-subnav-line');
  $secondary_attributes->addClass('uk-margin-bottom-remove');
  $variables['secondary_attributes'] = $secondary_attributes;
}
