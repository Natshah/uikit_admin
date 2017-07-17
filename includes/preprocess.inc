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
  $variables['header_wrapper_attributes'] = $page_attributes['header_wrapper_attributes'];
  $variables['header_attributes'] = $page_attributes['header_attributes'];
  $variables['pre_content_attributes'] = $page_attributes['pre_content_attributes'];
  $variables['breadcrumb_attributes'] = $page_attributes['breadcrumb_attributes'];
  $variables['highlighted_attributes'] = $page_attributes['highlighted_attributes'];
  $variables['help_attributes'] = $page_attributes['help_attributes'];
  $variables['content_wrapper_attributes'] = $page_attributes['content_wrapper_attributes'];
  $variables['content_grid_attributes'] = $page_attributes['content_grid_attributes'];
  $variables['content_attributes'] = $page_attributes['content_attributes'];
}

/**
 * Implements template_preprocess_admin_block_content().
 */
function uikit_admin_preprocess_admin_block_content(&$variables) {
  $attributes = new Attribute;
  $attributes->addClass('uk-list');
  $attributes->addClass('uk-list-line');
  $attributes->addClass('uk-margin-remove');
  $attributes->addClass('uk-admin-list-group');
  $variables['attributes'] = $attributes;
}

/**
 * Implements template_preprocess_details().
 */
function uikit_admin_preprocess_details(&$variables) {
  // Set the accordion attributes.
  $attributes = $variables['attributes'];
  $accordion_attributes = new Attribute;

  foreach ($attributes as $attribute => $value) {
    if ($attribute != 'class' && $attribute != 'open') {
      $accordion_attributes->setAttribute($attribute, $value);
    }
  }
  $accordion_attributes->addClass('uk-form-row');
  $accordion_attributes->addClass('uk-accordion');

  // Set the data-uk-accordion attribute based on the #open value.
  $open = isset($variables['element']['#open']) ? $variables['element']['#open'] : FALSE;
  if ($open) {
    $accordion_attributes->setAttribute('data-uk-accordion', '{showfirst: true}');
  }
  else {
    $accordion_attributes->setAttribute('data-uk-accordion', '{showfirst: false}');
  }

  $variables['accordion_attributes'] = $accordion_attributes;

  // Set the accordion title attributes.
  $accordion_title_attributes = new Attribute;
  $accordion_title_attributes->addClass('uk-accordion-title');
  $variables['accordion_title_attributes'] = $accordion_title_attributes;

  // Set the accordion content attributes.
  $accordion_content_attributes = new Attribute;
  $accordion_content_attributes->addClass('uk-accordion-content');
  $variables['accordion_content_attributes'] = $accordion_content_attributes;

  // Set the error classes.
  $error_classes = new Attribute;
  $error_classes->addClass('uk-alert');
  $error_classes->addClass('uk-alert-danger');
  $variables['error_classes'] = $error_classes;

  // Set the description attributes.
  $description_attributes = new Attribute;
  $description_attributes->addClass('uk-form-help-block');
  $description_attributes->addClass('uk-margin-small-bottom');
  $variables['description_attributes'] = $description_attributes;
}

/**
 * Implements hook_form_alter().
 */
function uikit_admin_preprocess_form(&$variables) {
  $form_id = $variables['element']['#form_id'];
  $orientation = 'stacked';

  // Set the orientation of the form based on the form id.
  switch ($form_id) {
    case 'views_exposed_form':
    case 'view_preview_form':
      $orientation = 'horizontal';
      break;
  }

  // Set the orientation variable.
  $variables['orientation'] = $orientation;
}

/**
 * Implements template_preprocess_input().
 */
function uikit_admin_preprocess_input(&$variables) {
  $type = $variables['element']['#type'];

  if ($type == 'submit') {
    // Set the value variable so we can change submit buttons from an <input>
    // to a <button> element.
    if (is_object($variables['element']['#value'])) {
      $value = $variables['element']['#value']->getUntranslatedString();
    }
    else {
      $value = $variables['element']['#value'];
    }
    $variables['value'] = t('@value', ['@value' => $value]);
    $views_ui_dispay_buttons = UIkitAdmin::getViewsUIDisplayButtons();

    // Bypass doing anything with Views UI display buttons, which are assigned
    // a different template.
    // @see uikit_admin_theme_suggestions_input_alter()
    // @see input--views-ui.html.twig
    if (!in_array($value, $views_ui_dispay_buttons)) {
      // Add the uk-button class to all buttons.
      $variables['attributes']['class'][] = 'uk-button';

      switch ($value) {
        // Add uk-button-* modifier class based on the value of the button.
        case 'Add and configure @types':
        case 'Save':
        case 'Save blocks':
        case 'Save configuration':
        case 'Update':
          $variables['attributes']['class'][] = 'uk-button-primary';
          break;
      }
    }
  }
}

/**
 * Implements template_preprocess_links() for dropbutton links.
 */
function uikit_admin_preprocess_links__dropbutton(&$variables) {
  $links_id = isset($variables['attributes']['id']) ? $variables['attributes']['id'] : '';
  $theme_hook = isset($variables['theme_hook_original']) ? $variables['theme_hook_original'] : [];
  $operations_links = $theme_hook && $theme_hook == 'links__dropbutton__operations';
  $variables['dropdown_button_attributes'] = new Attribute;
  $variables['dropdown_button_attributes']->addClass('uk-button');

  // Add the uk-button-primary class based on the type of dropbutton is set,
  // ignoring if the dropdown links are for Views UI and operations links.
  if ($links_id != 'views-display-extra-actions' && !$operations_links) {
    $variables['dropdown_button_attributes']->addClass('uk-button-primary');

    if (isset($variables['dropbutton'])) {
      if ($variables['dropbutton']['link']) {
        $variables['dropbutton']['link']['#options']['attributes']['class'][] = 'uk-button-primary';
      }
      elseif ($variables['dropbutton']['text_attributes']) {
        $variables['dropbutton']['text_attributes']['class'][] = 'uk-button-primary';
      }
    }
  }
  elseif ($operations_links) {
    // Reset the attributes for operations links.
    $variables['attributes'] = new Attribute;
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
  $secondary_attributes->setAttribute('id', 'tasks--secondary');
  $secondary_attributes->addClass('uk-subnav');
  $secondary_attributes->addClass('uk-subnav-line');
  $secondary_attributes->addClass('uk-margin-bottom-remove');
  $variables['secondary_attributes'] = $secondary_attributes;
}

/**
 * Implements template_preprocess_region().
 */
function uikit_admin_preprocess_region(&$variabes) {
  $region = $variabes['region'];
  $attributes = $variabes['attributes'];

  switch ($region) {
    case 'pre_content':
    case 'breadcrumb':
      $region_attributes = new Attribute;
      $region_attributes->setAttribute('id', $attributes['id']);
      $variabes['attributes'] = $region_attributes;
      break;
  }
}

/**
 * Implements hook_preprocess_HOOK() for status-report-general-info.html.twig.
 */
function uikit_admin_preprocess_status_report_general_info(&$variables) {
  $apache = substr($variables['webserver']['value'], 0, 6) === 'Apache';
  $nginx = substr($variables['webserver']['value'], 0, 5) === 'nginx';

  if ($apache) {
    $variables['webserver']['icon'] = 'icon-apache';
  }
  elseif ($nginx) {
    $variables['webserver']['icon'] = 'icon-nginx';
  }
  else {
    $variables['webserver']['icon'] = 'uk-icon-server uk-text-muted';
  }

  if (isset($variables['cron']['description']) && $variables['cron']['description']) {
    $cron_links = $variables['cron']['description'];

    foreach ($cron_links[0] as $index => $cron_link) {
      if (isset($cron_link['#prefix']) && $cron_link['#prefix'] == '<span class="cron-description__run-cron">') {
        $variables['cron']['run_cron_link'] = $cron_link;
      }
      else {
        $variables['cron']['description'] = $cron_link;
      }
    }
  }
}

/**
 * Implements template_preprocess_views_ui_views_listing_table().
 */
function uikit_admin_preprocess_views_ui_views_listing_table(&$variables) {
  $variables['attributes']['class'][] = 'uk-table';
  $variables['attributes']['class'][] = 'uk-table-striped';
  $variables['attributes']['class'][] = 'uk-table-hover';
}
